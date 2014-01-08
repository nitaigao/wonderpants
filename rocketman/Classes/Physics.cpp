#include "Physics.h"

#include "Common.h"

#include "Box2D.h"
#include "PhysicsDataLoader.h"
#include "ContactListener.h"
#include "LookAtData.h"
#include "SpatialDecorator.h"

#include "RayCastLineOfSightResult.h"

#include "cocos2d.h"
USING_NS_CC;

#include "Component.h"

#include "GLES-Render.h"

#define PTM_RATIO 32.0f

static const char* SPATIAL_ATTR_X = "x";
static const char* SPATIAL_ATTR_Y = "y";
static const char* SPATIAL_ATTR_ROTATION = "rotation";

Physics::~Physics() {
  SAFE_DELETE(world_);
  SAFE_DELETE(contactListener_);
  SAFE_DELETE(debugDraw_);
}

Physics::Physics() 
  : world_(new b2World(b2Vec2(0.0f, -10.0f), true))
  , accumulator_(0)
  , contactListener_(0) {
    
  world_->SetContinuousPhysics(false);
  world_->SetAutoClearForces(false);
  
  b2BodyDef groundBodyDef;
  groundBodyDef.position.Set(0, 0); // bottom-left corner
  
  b2Body* groundBody = world_->CreateBody(&groundBodyDef);
  
  float groundDensity = 2;

  CCSize screenSize = CCDirector::sharedDirector()->getWinSize();
  
  b2PolygonShape groundBoxTop;
  groundBoxTop.SetAsBox(screenSize.width/PTM_RATIO, 0.1, b2Vec2(0, screenSize.height/PTM_RATIO), 0);
  groundBody->CreateFixture(&groundBoxTop, groundDensity);
  
  b2EdgeShape groundBoxLeft;
  groundBoxLeft.Set(b2Vec2(0,screenSize.height/PTM_RATIO), b2Vec2(0,0));
  groundBody->CreateFixture(&groundBoxLeft, groundDensity);
  
  b2EdgeShape groundBoxRight;
  groundBoxRight.Set(b2Vec2(screenSize.width/PTM_RATIO,screenSize.height/PTM_RATIO), b2Vec2(screenSize.width/PTM_RATIO,0));
  groundBody->CreateFixture(&groundBoxRight, groundDensity);
  
//  for (b2Fixture* f = groundBody->GetFixtureList(); f; f = f->GetNext()) {
//    b2Filter filter = f->GetFilterData();
//    filter.maskBits = 0xffff;
//    filter.categoryBits = 0xffff;
//    f->SetFilterData(filter);
//  }
  
  PhysicsDataLoader().cache("physics.plist");
  
  debugDraw_ = new GLESDebugDraw(PTM_RATIO * CC_CONTENT_SCALE_FACTOR());
  world_->SetDebugDraw(debugDraw_);
    
  uint32 flags = 0;
  flags += b2Draw::e_shapeBit;
  flags += b2Draw::e_jointBit;
  flags += b2Draw::e_aabbBit;
  flags += b2Draw::e_pairBit;
  flags += b2Draw::e_centerOfMassBit;

//  debugDraw->SetFlags(flags);
}

void Physics::setContactListener(b2ContactListener* listener) {
  SAFE_DELETE(contactListener_);
  contactListener_ = listener;
  world_->SetContactListener(listener);
}

void Physics::drawDebug() {
	glDisable(GL_TEXTURE_2D);
	glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	
	world_->DrawDebugData();
  
	glEnable(GL_TEXTURE_2D);
	glEnableClientState(GL_COLOR_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
}

void Physics::update(float dt) {
  int velocityIters = 10;
  int positionIters = 8;
  
  float step = 1.0f/420.0f;
  
  if (dt > 0.25f) {
    dt = 0.25f;
  }
  
  accumulator_ += dt;
  
  while (accumulator_ >= step) {
    world_->Step(step, velocityIters, positionIters);
    world_->ClearForces();
    accumulator_ -= step;
  }
  
  world_->Step(accumulator_, velocityIters, positionIters);
  world_->ClearForces();
  
  for (const LookAtData& lookAt : lookAts_) {
    setLookAt(lookAt);
  }

  for (b2Body* b = world_->GetBodyList(); b; b = b->GetNext()) {
    if (b->GetUserData() != NULL) {
      Component *actor = (Component*)b->GetUserData();
      
      float x = b->GetPosition().x * PTM_RATIO;
      actor->setAttr(SPATIAL_ATTR_X, x);

      float y = b->GetPosition().y * PTM_RATIO;
      actor->setAttr(SPATIAL_ATTR_Y, y);
      
      int rotation = -1 * CC_RADIANS_TO_DEGREES(b->GetAngle());
      actor->setAttr(SPATIAL_ATTR_ROTATION, rotation);
    }	
  }
}

void Physics::setLookAt(const LookAtData &lookAt) {
  b2Body* toBody = getBody(lookAt.to);
  Component* toSpatialComponent = static_cast<Component*>(toBody->GetUserData());
  SpatialDecorator toSpatial(toSpatialComponent);
  CCPoint toPosition = CCPointMake(toSpatial.x(), toSpatial.y());

  b2Body* fromBody = getBody(lookAt.from);
  Component* fromSpatialComponent = static_cast<Component*>(fromBody->GetUserData());
  SpatialDecorator fromSpatial(fromSpatialComponent);
  CCPoint fromPosition = CCPointMake(fromSpatial.x(), fromSpatial.y());
  
  CCPoint targetFromSubject = ccpSub(toPosition, fromPosition);
  
  CCPoint up = CCPointMake(0, 1);
  
  float angleToTarget = ccpAngle(up, targetFromSubject);
  float crossToTarget = ccpCross(up, targetFromSubject);
  float rotationToTarget = crossToTarget < 0 ? angleToTarget : -angleToTarget;

  for (b2Body* b = world_->GetBodyList(); b; b = b->GetNext()) {
    if (!b->GetUserData()) continue;
    Component* spatial = (Component*)b->GetUserData();    
    if (spatial->label() == lookAt.from) {
      b->SetTransform(b->GetPosition(), -rotationToTarget + CC_DEGREES_TO_RADIANS(lookAt.offset));
    }
  }
}

void Physics::addObject(int x, int y, float rotation, const String& data, const String& sim, bool allowSleep, bool gravity, bool isBullet, int label, Component* component) {
  b2BodyDef bodyDef;
  bodyDef.type = sim == "dynamic" ? b2_dynamicBody : b2_staticBody;
  bodyDef.position.Set(x/PTM_RATIO, y/PTM_RATIO);
  bodyDef.userData = component;
  bodyDef.angle = CC_DEGREES_TO_RADIANS(-rotation);
  bodyDef.fixedRotation = true;
  bodyDef.allowSleep = allowSleep;
  bodyDef.isGravitated = gravity;
  bodyDef.bullet = isBullet;
  
  b2Body *body = world_->CreateBody(&bodyDef);  
  
  if (data.length()) {
    PhysicsDataLoader().loadBody(body, data);
  }
}

void Physics::removeObject(int label) {
  for (b2Body* b = world_->GetBodyList(); b; b = b->GetNext()) {
    if (!b->GetUserData()) continue;
    Component* spatial = (Component*)b->GetUserData();    
    if (spatial->label() == label) {
      world_->DestroyBody(b);
    }	
  }  
}

void Physics::setDynamic(int label) {
  for (b2Body* b = world_->GetBodyList(); b; b = b->GetNext()) {
    if (!b->GetUserData()) continue;
    Component* spatial = (Component*)b->GetUserData();    
    if (spatial->label() == label) {
      b->SetType(b2_dynamicBody);
      b->SetAwake(true);
    }	
  }
}

void Physics::applyImpulse(int label, float impulse, const b2Vec2& direction) {
  for (b2Body* b = world_->GetBodyList(); b; b = b->GetNext()) {
    if (!b->GetUserData()) continue;
    Component* spatial = (Component*)b->GetUserData();    
    if (spatial->label() == label) {
      b2Vec2 strength(direction.x * impulse, direction.y * impulse);
      b->ApplyLinearImpulse(strength, b->GetWorldCenter());
    }
  }
}

void Physics::stopMotion(int label) {
  for (b2Body* b = world_->GetBodyList(); b; b = b->GetNext()) {
    if (!b->GetUserData()) continue;
    Component* spatial = (Component*)b->GetUserData();    
    if (spatial->label() == label) {
      b->SetLinearDamping(0);
      b->SetAngularDamping(0);
      b->SetAngularVelocity(0);
      b->SetLinearVelocity(b2Vec2(0,0));
      b->SetLinearVelocity(b2Vec2(-b->GetLinearVelocity()));
    }
  }  
}

void Physics::setTranslation(float x, float y, int label) {
  for (b2Body* b = world_->GetBodyList(); b; b = b->GetNext()) {
    if (b->GetUserData() != NULL) {
      Component* spatial = (Component*)b->GetUserData();    
      if (spatial->label() == label) {
        b2Vec2 position(x/PTM_RATIO, y/PTM_RATIO);
        b->SetTransform(position, b->GetAngle());
      }
    }
  }
}

void Physics::translate(float x, float y, int label) {
  for (b2Body* b = world_->GetBodyList(); b; b = b->GetNext()) {
    if (b->GetUserData() != NULL) {
      Component* spatial = (Component*)b->GetUserData();    
      if (spatial->label() == label) {
        b2Vec2 position = b->GetPosition() + b2Vec2(x/PTM_RATIO, y/PTM_RATIO);
        b->SetTransform(position, b->GetAngle());
      }
    }
  }
}

void Physics::rotate(float amount, int label) {
  for (b2Body* b = world_->GetBodyList(); b; b = b->GetNext()) {
    if (b->GetUserData() != NULL) {
      Component* spatial = (Component*)b->GetUserData();    
      if (spatial->label() == label) {
        float newAngle = b->GetAngle() + amount;
        b->SetTransform(b->GetPosition(), newAngle);
      }
    }
  }
}

void Physics::setRotation(float amount, int label) {
  for (b2Body* b = world_->GetBodyList(); b; b = b->GetNext()) {
    if (b->GetUserData() != NULL) {
      Component* spatial = (Component*)b->GetUserData();    
      if (spatial->label() == label) {
        b->SetTransform(b->GetPosition(), amount);
      }
    }
  }
}

void Physics::disableCollisions(int label) {
  for (b2Body* b = world_->GetBodyList(); b; b = b->GetNext()) {
    if (b->GetUserData() != NULL) {
      Component* spatial = (Component*)b->GetUserData();    
      if (spatial->label() == label) {
        for (b2Fixture* f = b->GetFixtureList(); f; f = f->GetNext()) {
          b2Filter filter = f->GetFilterData();
          filter.maskBits = 0xffff & ~0x0001;
          f->SetFilterData(filter);
        }
      }
    }
  }
}

void Physics::applyForce(int x, int y, float strength, int label) {
  for (b2Body* b = world_->GetBodyList(); b; b = b->GetNext()) {
    if (b->GetUserData() != NULL) {
      Component* spatial = (Component*)b->GetUserData();    
      if (spatial->label() == label) {
        b2Vec2 force(x * strength, y * strength);
        b->ApplyForce(force, b->GetWorldCenter());
      }
    }
  }  
}

void Physics::adjustRope(int fromLabel, int toLabel, float amount) {

}

void Physics::setLinearDampening(float dampening, int label) {
  for (b2Body* b = world_->GetBodyList(); b; b = b->GetNext()) {
    if (b->GetUserData() != NULL) {
      Component* spatial = (Component*)b->GetUserData();    
      if (spatial->label() == label) {
        b->SetLinearDamping(dampening);
      }
    }
  }  
}

void Physics::setShape(const String& shapeName, int label) {
  for (b2Body* b = world_->GetBodyList(); b; b = b->GetNext()) {
    if (b->GetUserData() != NULL) {
      Component* spatial = (Component*)b->GetUserData();    
      if (spatial->label() == label) {
        for (b2Fixture* fixture = b->GetFixtureList(); fixture != nullptr; fixture = b->GetFixtureList()) {
          b->DestroyFixture(fixture);
        }
        PhysicsDataLoader().loadBody(b, shapeName);
      }
    }
  }    
}

void Physics::createRope(int from, int to) {
  b2Body* toBody = getBody(to);
  b2Body* fromBody = getBody(from);
  
  b2DistanceJointDef jointDef;
  jointDef.Initialize(fromBody, toBody, fromBody->GetWorldCenter(), toBody->GetWorldCenter());  
  world_->CreateJoint(&jointDef);
}

b2Body* Physics::getBody(int label) {
  for (b2Body* b = world_->GetBodyList(); b; b = b->GetNext()) {
    if (b->GetUserData() != NULL) {
      Component* spatial = (Component*)b->GetUserData();    
      if (spatial->label() == label) {
        return b;
      }
    }
  }
  return 0;
}

void Physics::deleteRope() {
  for (b2Body* b = world_->GetBodyList(); b; b = b->GetNext()) {
    for (b2JointEdge* jointEdge = b->GetJointList(); b->GetJointList(); jointEdge = b->GetJointList()) {
      world_->DestroyJoint(jointEdge->joint);
    }
  }
  lookAts_.removeAllObjects();
}  

void Physics::lookAt(int from, int to, int offset) {
  LookAtData lookAt(to, from, offset);
  lookAts_.addObject(lookAt);
}

bool Physics::isLineOfSight(int from, int to) {
  b2Body* fromBody = getBody(from);
  b2Body* toBody = getBody(to);
  
  RayCastLineOfSightResult result;
  world_->RayCast(&result, fromBody->GetPosition(), toBody->GetPosition());
  
  return result.getHits() == 1;
}

void Physics::setSensor(int label, bool isSensor) {
  for (b2Body* b = world_->GetBodyList(); b; b = b->GetNext()) {
    if (b->GetUserData() != NULL) {
      Component *actor = (Component*)b->GetUserData();
      if (actor->label() == label) {
        for (b2Fixture* f = b->GetFixtureList(); f; f = f->GetNext()) {
          f->SetSensor(isSensor);
        }
      }
    }
  }  
}

void Physics::setStatic(int label) {
  for (b2Body* b = world_->GetBodyList(); b; b = b->GetNext()) {
    if (b->GetUserData() != NULL) {
      Component *actor = (Component*)b->GetUserData();
      if (actor->label() == label) {
        b->SetType(b2_staticBody);
        b->SetAwake(true);
      }
    }
  }
}

void Physics::setActive(bool isActive, int label) {
  for (b2Body* b = world_->GetBodyList(); b; b = b->GetNext()) {
    if (b->GetUserData() != NULL) {
      Component *actor = (Component*)b->GetUserData();
      if (actor->label() == label) {
        b->SetActive(isActive);
      }
    }
  }    
}
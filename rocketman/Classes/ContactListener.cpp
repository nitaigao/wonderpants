#include "ContactListener.h"

#include "Box2D.h"
#include "Component.h"
#include "Level.h"
#include "EventSystem.h"

#include "cocos2d.h"

void ContactListener::registerHit(b2Fixture* source, b2Fixture* target, b2Contact* contact) {
  // things like the floor are int he physics world but arent entities so dont have components or labels
  int sourceLabel = -1;

  if (source->GetBody()->GetUserData()) {
    Component* sourceSpatial = (Component*)source->GetBody()->GetUserData();
    sourceLabel = sourceSpatial->label();
  }
  
  int targetLabel = -1;
  String targetMaterial;
  
  if (target->GetBody()->GetUserData()) {
    Component* targetSpatial = (Component*)target->GetBody()->GetUserData();
    
    Component* targetPhysical = level_->component("physical", targetSpatial->label());
    targetMaterial = targetPhysical->attr("material").string();
    targetLabel = targetSpatial->label();
  }
  
  eventSystem_->postEvent("collision", sourceLabel, targetLabel, targetMaterial);
}

void ContactListener::BeginContact(b2Contact* contact) { 
  registerHit(contact->GetFixtureA(), contact->GetFixtureB(), contact);
  registerHit(contact->GetFixtureB(), contact->GetFixtureA(), contact);
}
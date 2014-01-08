#ifndef Physics_H_
#define Physics_H_

#include "Common.h"

#include "LookAtData.h"

class String;
class b2World;
class b2Vec2;
class b2Body;
class Component;
class b2ContactListener;
class GLESDebugDraw;

class Physics {
  
public:
  
  Physics();
  
  ~Physics();
  
public:

  void addObject(int x, int y, float rotation, const String& data, const String& sim, bool allowSleep, bool gravity, bool isBullet, int label, Component* component);
  
  void removeObject(int label);
  
  void setDynamic(int label);
  
  void applyImpulse(int label, float strength, const b2Vec2& direction);
  
  void applyForce(int x, int y, float strength, int label);
  
  void adjustRope(int fromLabel, int toLabel, float amount);
  
  void stopMotion(int label);
  
  void setLinearDampening(float dampening, int label);
  
  void setShape(const String& shapeName, int label);
  
  void createRope(int from, int to);
  
  void deleteRope();
  
  void lookAt(int from, int to, int offset);
  
  bool isLineOfSight(int from, int to);
  
  void setSensor(int label, bool isSensor);
  
  void setStatic(int label);
  
  void setActive(bool isActive, int label);
  
public:
  
  void drawDebug();
  
  void update(float dt);
  
  void setContactListener(b2ContactListener* listener);
  
public:
  
  void setTranslation(float x, float y, int label);
  
  void translate(float x, float y, int label);
  
  void rotate(float amount, int label);
  
  void setRotation(float amount, int label);
  
  void disableCollisions(int label);
  
private:
  
  b2Body* getBody(int label);
  void setLookAt(const LookAtData& lookAt);
  
  b2World* world_;
  float accumulator_;
  
  b2ContactListener* contactListener_;
  GLESDebugDraw* debugDraw_;
  
  Array<LookAtData> lookAts_;
  
};

#endif

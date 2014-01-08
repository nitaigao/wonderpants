#ifndef PhysicsScriptHandler_H_
#define PhysicsScriptHandler_H_

class lua_State;
class Physics;
class Component;
class String;

namespace cocos2d {
  class CCPoint;
};

#include "ScriptHandler.h"

class PhysicsScriptHandler : public ScriptHandler {
  
public:
  
  ~PhysicsScriptHandler();
  PhysicsScriptHandler(lua_State* state, Physics* physics, Component* component);
  
public:
  
  static int lua_SetDynamic(lua_State* l);
  void setDynamic(int label);

  static int lua_ApplyImpulse(lua_State* l);
  void applyImpulse(int label, float strength, const cocos2d::CCPoint& direction);
  
  static int lua_StopMotion(lua_State* l);
  void stopMotion(int label);
  
  static int lua_DisableCollisions(lua_State* l);
  void disableCollisions(int label);
  
  static int lua_ApplyForce(lua_State* l);
  void applyForce(int x, int y, int label, float strength);
  
  static int lua_AdjustRope(lua_State* l);
  void adjustRope(int fromLabel, int toLabel, int amount);
  
  static int lua_SetShape(lua_State* l);
  void setShape(const String& shapeName, int label);
  
  static int lua_SetLinearDampening(lua_State* l);
  void setLinearDampening(float dampening, int label);
  
  static int lua_SetMaterial(lua_State* l);
  
  static int lua_LineOfSight(lua_State* l);
  bool isLineOfSight(int fromLabel, int toLabel);
  
  static int lua_SetSensor(lua_State* l);
  void setSensor(int label, bool isSensor);
  
  static int lua_MakeSensor(lua_State* l);  
  void makeSensor(int label);
  
  static int lua_SetStatic(lua_State* l);
  void setStatic(int label);
  
  static int lua_SetActive(lua_State* l);
  void setActive(bool active, int label);
  
  static int lua_RayHitWithin(lua_State* l);
  
  
  

  
private:
  
private:
  
  const char* name() { return "physics"; };
  
  Physics* physics_;
  Component* component_;
      
};

#endif

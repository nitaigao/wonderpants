#include "PhysicsScriptHandler.h"

extern "C" {
  #include "lua.h"
  #include "lualib.h"
  #include "lauxlib.h"
};

#include "Physics.h"
#include "ScriptUtils.h"

#include "b2Math.h"

PhysicsScriptHandler::~PhysicsScriptHandler() {
  
}

PhysicsScriptHandler::PhysicsScriptHandler(lua_State* l, Physics* physics, Component* component)
  : physics_(physics)
  , component_(component) {
  
  lua_newtable(l);
  
  lua_pushstring(l, "disable_collisions");
  lua_pushcfunction(l, lua_DisableCollisions);
  lua_settable(l, -3);
  
  lua_pushstring(l, "apply_impulse");
  lua_pushcfunction(l, lua_ApplyImpulse);
  lua_settable(l, -3);
  
  lua_pushstring(l, "apply_force");
  lua_pushcfunction(l, lua_ApplyForce);
  lua_settable(l, -3);
  
  lua_pushstring(l, "adjust_rope");
  lua_pushcfunction(l, lua_AdjustRope);
  lua_settable(l, -3);
  
  lua_pushstring(l, "set_shape");
  lua_pushcfunction(l, lua_SetShape); 
  lua_settable(l, -3);
  
  lua_pushstring(l, "set_sensor");
  lua_pushcfunction(l, lua_SetSensor);
  lua_settable(l, -3);
  
  lua_pushstring(l, "make_sensor");
  lua_pushcfunction(l, lua_MakeSensor);
  lua_settable(l, -3);
  
  lua_pushstring(l, "set_dynamic");
  lua_pushcfunction(l, lua_SetDynamic);
  lua_settable(l, -3);
  
  lua_pushstring(l, "set_static");
  lua_pushcfunction(l, lua_SetStatic);
  lua_settable(l, -3);
  
  lua_pushstring(l, "set_active");
  lua_pushcfunction(l, lua_SetActive);
  lua_settable(l, -3);
  
  lua_pushstring(l, "set_linear_dampening");
  lua_pushcfunction(l, lua_SetLinearDampening);
  lua_settable(l, -3);
  
  lua_pushstring(l, "stop_motion");
  lua_pushcfunction(l, lua_StopMotion);
  lua_settable(l, -3);
  
  lua_pushstring(l, "set_material");
  lua_pushcfunction(l, lua_SetMaterial);
  lua_settable(l, -3);
    
  lua_pushstring(l, "line_of_sight");
  lua_pushcfunction(l, lua_LineOfSight);
  lua_settable(l, -3);
  
  lua_pushstring(l, "ray_hit_within");
  lua_pushcfunction(l, lua_RayHitWithin);
  lua_settable(l, -3);
  
  lua_setglobal(l, "physics");
  
  lua_pushstring(l, "physics");
  lua_pushlightuserdata(l, this);
  lua_settable(l, LUA_REGISTRYINDEX);
}

int PhysicsScriptHandler::lua_DisableCollisions(lua_State* l) {
  int label = lua_tointeger(l, -1);
  lua_pop(l, 1);
  
  handler<PhysicsScriptHandler>(l, "physics")->disableCollisions(label);
  
  return 0;
};

void PhysicsScriptHandler::disableCollisions(int label) {
  physics_->disableCollisions(label);
}

int PhysicsScriptHandler::lua_ApplyImpulse(lua_State* l) {
  int label = lua_tonumber(l, LUA_STACK_TOP);
  lua_pop(l, 1);
  
  float strength = lua_tonumber(l, LUA_STACK_TOP);
  lua_pop(l, 1);
  
  CCPoint direction = lua_tovector(l, LUA_STACK_TOP);
  lua_pop(l, 1);
  
  handler<PhysicsScriptHandler>(l, "physics")->applyImpulse(label, strength, direction);
  return 0;
};

void PhysicsScriptHandler::applyImpulse(int label, float strength, const CCPoint& direction) {
  b2Vec2 directionVec(direction.x, direction.y);
  physics_->applyImpulse(label, strength, directionVec);
}

int PhysicsScriptHandler::lua_ApplyForce(lua_State* l) {
  int label = lua_tonumber(l, LUA_STACK_TOP);
  lua_pop(l, 1);
  
  float strength = lua_tonumber(l, LUA_STACK_TOP);
  lua_pop(l, 1);
  
  CCPoint direction = lua_tovector(l, LUA_STACK_TOP);
  lua_pop(l, 1);
  
  handler<PhysicsScriptHandler>(l, "physics")->applyForce(direction.x, direction.y, strength, label);

  return 0;
};

void PhysicsScriptHandler::applyForce(int x, int y, int label, float strength) {
  physics_->applyForce(x, y, strength, label);
}

int PhysicsScriptHandler::lua_AdjustRope(lua_State* l) {
  float amount = lua_tonumber(l, LUA_STACK_TOP);
  lua_pop(l, 1);
  
  int to_label = lua_tonumber(l, LUA_STACK_TOP);
  lua_pop(l, 1);
  
  int from_label = lua_tonumber(l, LUA_STACK_TOP);
  lua_pop(l, 1);
  
  handler<PhysicsScriptHandler>(l, "physics")->adjustRope(from_label, to_label, amount);

  return 0;
};

void PhysicsScriptHandler::adjustRope(int fromLabel, int toLabel, int amount) {
  physics_->adjustRope(fromLabel, toLabel, amount);
}

int PhysicsScriptHandler::lua_SetShape(lua_State* l) {
  int label = lua_tonumber(l, LUA_STACK_TOP);
  lua_pop(l, 1);
  
  std::string shapeName = lua_tostring(l, LUA_STACK_TOP);
  
  handler<PhysicsScriptHandler>(l, "physics")->setShape(shapeName, label);

  return 0;
};

void PhysicsScriptHandler::setShape(const String& shapeName, int label) {
  physics_->setShape(shapeName, label);
}

int PhysicsScriptHandler::lua_SetSensor(lua_State* l) {
  int label = lua_tonumber(l, LUA_STACK_TOP);
  lua_pop(l, 1);
  
  bool isSensor = lua_toboolean(l, LUA_STACK_TOP);
  lua_pop(l, 1);
  
  handler<PhysicsScriptHandler>(l, "physics")->setSensor(label, isSensor);  
  
  return 0;
};

void PhysicsScriptHandler::setSensor(int label, bool isSensor) {
  physics_->setSensor(label, isSensor);
}

int PhysicsScriptHandler::lua_MakeSensor(lua_State* l) {
  int label = lua_tonumber(l, LUA_STACK_TOP);
  lua_pop(l, 1);
  handler<PhysicsScriptHandler>(l, "physics")->makeSensor(label);  
  return 0;
};

void PhysicsScriptHandler::makeSensor(int label) {
  setSensor(label, true);
}

int PhysicsScriptHandler::lua_SetDynamic(lua_State* l) {
  int label = lua_tonumber(l, -1);
  lua_pop(l, 1);
  
  handler<PhysicsScriptHandler>(l, "physics")->setDynamic(label);
  
  return 0;
};

void PhysicsScriptHandler::setDynamic(int label) {
  physics_->setDynamic(label);
}

int PhysicsScriptHandler::lua_SetStatic(lua_State* l) {
  int label = lua_tonumber(l, -1);
  lua_pop(l, 1);
  handler<PhysicsScriptHandler>(l, "physics")->setStatic(label);
  return 0;
};

void PhysicsScriptHandler::setStatic(int label) {
  physics_->setStatic(label);
}

int PhysicsScriptHandler::lua_SetActive(lua_State* l) {
  int label = lua_tonumber(l, LUA_STACK_TOP);
  lua_pop(l, 1);
  
  bool active = lua_toboolean(l, LUA_STACK_TOP);
  lua_pop(l, 1);

  handler<PhysicsScriptHandler>(l, "physics")->setActive(active, label);
  
  return 0;
};

void PhysicsScriptHandler::setActive(bool active, int label) {
  physics_->setActive(active, label);
}

int PhysicsScriptHandler::lua_SetLinearDampening(lua_State* l) {
  int label = lua_tonumber(l, -1);
  lua_pop(l, 1);
  
  float dampening = lua_tonumber(l, -1);
  lua_pop(l, 1);

  handler<PhysicsScriptHandler>(l, "physics")->setLinearDampening(dampening, label);
  
  return 0;
};

void PhysicsScriptHandler::setLinearDampening(float dampening, int label) {
  physics_->setLinearDampening(dampening, label);
}

int PhysicsScriptHandler::lua_StopMotion(lua_State* l) {
  int label = lua_tointeger(l, -1);
  lua_pop(l, 1);
  handler<PhysicsScriptHandler>(l, "physics")->stopMotion(label);
  return 0;
};

void PhysicsScriptHandler::stopMotion(int label) {
  physics_->stopMotion(label);
}

int PhysicsScriptHandler::lua_SetMaterial(lua_State* l) {
  return 0;
};

int PhysicsScriptHandler::lua_LineOfSight(lua_State* l) {
  
  int fromLabel = lua_tonumber(l, LUA_STACK_TOP);
  lua_pop(l, 1);
  
  int toLabel = lua_tonumber(l, LUA_STACK_TOP);
  lua_pop(l, 1);

  bool result = handler<PhysicsScriptHandler>(l, "physics")->isLineOfSight(fromLabel, toLabel);
  lua_pushboolean(l, result);
  
  return 1;
}

bool PhysicsScriptHandler::isLineOfSight(int fromLabel, int toLabel) {
  return physics_->isLineOfSight(fromLabel, toLabel);
}

int PhysicsScriptHandler::lua_RayHitWithin(lua_State* l) {
  return 0;
};

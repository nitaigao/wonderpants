#include "TransformScriptHandler.h"

#include "ScriptUtils.h"
#include "Component.h"
#include "Physics.h"

extern "C" {
  #include "lua.h"
  #include "lualib.h"
  #include "lauxlib.h"
};

TransformScriptHandler::TransformScriptHandler(lua_State* state, Component* component, Physics* physics) 
  : component_(component) 
  , physics_(physics) {
    
  lua_newtable(state);
  lua_pushstring(state, "rotate");
  lua_pushcfunction(state, l_rotate);
  lua_settable(state, -3);
  
  lua_pushstring(state, "set_rotation");
  lua_pushcfunction(state, l_setRotation);
  lua_settable(state, -3);
  
  
  lua_pushstring(state, "set_rotation");
  lua_pushcfunction(state, l_setRotation);
  lua_settable(state, -3);  
  
  lua_pushstring(state, "translate");
  lua_pushcfunction(state, l_translate);
  lua_settable(state, -3);
  
  lua_pushstring(state, "set_translation");
  lua_pushcfunction(state, l_setTranslation);
  lua_settable(state, -3);
  
  lua_pushstring(state, "look_at");
  lua_pushcfunction(state, l_lookAt);
  lua_settable(state, -3);
  
  lua_pushstring(state, "stop_look_at");
  lua_pushcfunction(state, l_stopLookAt);
  lua_settable(state, -3);
  
  lua_setglobal(state, "transform");
  
  lua_pushstring(state, "transform");
  lua_pushlightuserdata(state, this);
  lua_settable(state, LUA_REGISTRYINDEX);
}

int TransformScriptHandler::l_setTranslation(lua_State* l) {
  int label = -1;
  
  if (lua_gettop(l) == 4) {
    label = lua_tointeger(l, LUA_STACK_TOP);
    lua_pop(l, 1);
  }
  
  float y = lua_tonumber(l, lua_gettop(l));
  lua_pop(l, 1);
  float x = lua_tonumber(l, lua_gettop(l));
  lua_pop(l, 1);
  
  handler<TransformScriptHandler>(l, "transform")->setTranslation(x, y, label);
  return 0;
}

void TransformScriptHandler::setTranslation(float x, float y, int label) {
  label = (label == -1) ? component_->label() : label;
  physics_->setTranslation(x, y, label);
}

int TransformScriptHandler::l_translate(lua_State* l) {
  int label = -1;
  
  if (lua_gettop(l) == 4) {
    label = lua_tointeger(l, LUA_STACK_TOP);
    lua_pop(l, 1);
  }
  
  float y = lua_tonumber(l, lua_gettop(l));
  lua_pop(l, 1);
  
  float x = lua_tonumber(l, lua_gettop(l));
  lua_pop(l, 1);

  handler<TransformScriptHandler>(l, "transform")->translate(x, y, label);
  
  return 0;
}

void TransformScriptHandler::translate(float x, float y, int label) {
  label = (label == -1) ? component_->label() : label;
  physics_->translate(x, y, label);
}

int TransformScriptHandler::l_setRotation(lua_State* l) {
  float rotation = lua_tonumber(l, LUA_STACK_TOP);
  lua_pop(l, 1); // pop the rotate function param
  
  handler<TransformScriptHandler>(l, "transform")->setRotation(rotation);

  return 0;
}

void TransformScriptHandler::setRotation(float rotation) {
  physics_->setRotation(rotation, component_->label());
}

int TransformScriptHandler::l_rotate(lua_State* l) {
  float rotation = lua_tonumber(l, LUA_STACK_TOP);
  lua_pop(l, 1); // pop the rotate function param
  
  handler<TransformScriptHandler>(l, "transform")->rotate(rotation);

  return 0;
}

void TransformScriptHandler::rotate(float rotation) {
  physics_->rotate(rotation, component_->label());
}

int TransformScriptHandler::l_lookAt(lua_State* l) {
  int offset = lua_tonumber(l, LUA_STACK_TOP);
  lua_pop(l, 1);
  
  int target = lua_tonumber(l, LUA_STACK_TOP);
  lua_pop(l , 1);
  
  handler<TransformScriptHandler>(l, "transform")->lookAt(offset, target);

  return 0;
}

void TransformScriptHandler::lookAt(int offset, int target) {
  physics_->lookAt(component_->label(), target, offset);
}

int TransformScriptHandler::l_stopLookAt(lua_State* l) {
  return 0;
}

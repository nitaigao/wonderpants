#include "EntityScriptHandler.h"

extern "C" {
  #include "lua.h"
  #include "lualib.h"
  #include "lauxlib.h"
};

#include "Common.h"
#include "Level.h"
#include "Component.h"
#include "ScriptUtils.h"
#include "LevelCache.h"
#include "Entity.h"

EntityScriptHandler::EntityScriptHandler(lua_State* state, Component* component, Level* level) 
  : level_(level)
  , component_(component) {
  lua_newtable(state);
 
  lua_pushstring(state, "destroy");
  lua_pushcfunction(state, l_destroy);
  lua_settable(state, -3);
    
  lua_pushstring(state, "spawn");
  lua_pushcfunction(state, l_spawn);
  lua_settable(state, -3);
    
  lua_setglobal(state, "entity");
  
  lua_pushstring(state, "entity");
  lua_pushlightuserdata(state, this);
  lua_settable(state, LUA_REGISTRYINDEX);
}

int EntityScriptHandler::l_destroy(lua_State* l) {
  lua_pushstring(l, "entity");
  lua_gettable(l, LUA_REGISTRYINDEX);
  
  EntityScriptHandler* handler = (EntityScriptHandler*)lua_touserdata(l, -1);
  lua_pop(l, 1);
  
  int label = -1;
  if (lua_gettop(l) == 2) {
    label = lua_tointeger(l, -1);
    lua_pop(l, 1);
  }

  handler->destroy(label);
  
  return 0;
}

void EntityScriptHandler::destroy(int label) {
  label = label == -1 ? component_->label() : label;
  level_->destroyComponents(label);
}


int EntityScriptHandler::l_spawn(lua_State* l) {
  
  float rotation = lua_tonumber(l, -1);
  int y = lua_tonumber(l, -2);
  int x = lua_tonumber(l, -3);
  String type = lua_tostring(l, -4);
  lua_pop(l, 4);
  
  int label = handler<EntityScriptHandler>(l, "entity")->spawn(type, x, y, rotation);
  
  lua_pushinteger(l, label);
  
  return 1;
}

int EntityScriptHandler::spawn(const String& type, float x, float y, int rotation) {
  String path = type.concat(".prefab");
  Entity* entity = LevelCache::sharedCache()->loadPrefab(path);
  
  int label = level_->addEntity(entity);
  SAFE_DELETE(entity);
  
  Component* spatial = level_->component("spatial", label);
  
  spatial->setAttr("x", x);
  spatial->setAttr("y", y);
  spatial->setAttr("rotation", rotation);
  
  level_->setupComponents(label);
  
  return label;
}
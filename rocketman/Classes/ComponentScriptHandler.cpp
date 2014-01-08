#include "ComponentScriptHandler.h"

#include "Common.h"

#include "Component.h"
#include "Level.h"
#include "AttributeScriptHandler.h"
#include "ScriptUtils.h"

extern "C" {
  #include "lua.h"
  #include "lualib.h"
  #include "lauxlib.h"
};

ComponentScriptHandler::ComponentScriptHandler(lua_State* state, Component* component, Level* level)
  : l_(state)
  , component_(component)
  , level_(level) {
    
  lua_newtable(l_);
  lua_pushstring(l_, "get");
  lua_pushcfunction(l_, &ComponentScriptHandler::lua_getComponent);
  lua_settable(l_, -3);
  
  lua_pushstring(l_, "get_all");
  lua_pushcfunction(l_, ComponentScriptHandler::lua_getComponents);
  lua_settable(l_, -3);
  
  lua_setglobal(l_, "component");
    
  lua_pushstring(state, "component");
  lua_pushlightuserdata(state, this);
  lua_settable(state, LUA_REGISTRYINDEX);
}

int ComponentScriptHandler::lua_getComponent(lua_State* l) {
  lua_pushstring(l, "component");
  lua_gettable(l, LUA_REGISTRYINDEX);
  
  ComponentScriptHandler* handler = (ComponentScriptHandler*)lua_touserdata(l, -1);
  lua_pop(l, 1);
  
  int label = -1;
  
  if (lua_gettop(l) == 3) { // optional label has been passed in
    label = lua_tonumber(l, -1);
    lua_pop(l, 1);
  }
  
  String type = lua_tostring(l, -1);
  lua_pop(l, 1);
    
  Component* component = handler->getComponent(type, label);
  pushComponent(l, component);
    
  return 1;
}

Component* ComponentScriptHandler::getComponent(const String& type, int label) {
  label = (label == -1) ? component_->label() : label;
  return level_->component(type, label);
}

int ComponentScriptHandler::lua_getComponents(lua_State* l) {
  String type = lua_tostring(l, -1);
  lua_pop(l, 1);

  Array<Component*> components = handler<ComponentScriptHandler>(l, "component")->getComponents(type);
  
  lua_newtable(l);
  
  int i = 1;
  for (Component* component : components) {    
    lua_pushnumber(l, i++);
    pushComponent(l, component);
    lua_settable(l, -3);
  }
  
  return 1;
}

Array<Component*> ComponentScriptHandler::getComponents(const String& type) {
  return level_->components(type);
}
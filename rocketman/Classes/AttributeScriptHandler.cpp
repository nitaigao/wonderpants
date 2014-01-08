#include "AttributeScriptHandler.h"

#include "Common.h"

#include "Level.h"
#include "LuaState.h"
#include "Value.h"

extern "C" {
  #include "lua.h"
  #include "lualib.h"
  #include "lauxlib.h"
};

#include "Component.h"

#include "ScriptUtils.h"

AttributeScriptHandler::AttributeScriptHandler(lua_State* state, Component* component, Level* level) 
  : l_(state)
  , component_(component)
  , level_(level) {
    
  lua_newtable(l_);
  lua_pushinteger(state, component->label());
  lua_setfield(l_, -2, "label");
    
  lua_pushstring(l_, component->type().c_str());
  lua_setfield(l_, -2, "type");
    
  lua_newtable(l_);
    
  lua_pushcfunction(state, lua_getAttr);
  lua_setfield(state, -2, "__index");
  
  lua_pushcfunction(state, lua_setAttr);
  lua_setfield(state, -2, "__newindex");
  lua_setmetatable(state, -2);
    
  lua_setglobal(state, "this");
    
  lua_pushstring(state, "attr");
  lua_pushlightuserdata(state, this);
  lua_settable(state, LUA_REGISTRYINDEX);
}

int AttributeScriptHandler::lua_getAttr(lua_State* l) {
  lua_pushstring(l, "attr");
  lua_gettable(l, LUA_REGISTRYINDEX);
  
  AttributeScriptHandler* handler = (AttributeScriptHandler*)lua_touserdata(l, -1);
  lua_pop(l, 1);
    
  String attr = lua_tostring(l, -1);
  lua_pop(l, 1);
  
  lua_getfield(l, -1, "type");
  String type = lua_tostring(l, -1);
  lua_pop(l, 1);
  
  lua_getfield(l, -1, "label");
  int label = lua_tointeger(l, -1);
  lua_pop(l, 1);
  
  Value value = handler->getAttr(attr, label, type);
  lua_pushvalue(l, value);
  
  return 1;
}

Value AttributeScriptHandler::getAttr(const String& key, int label, const String& type) {
  
  if (type.hash() == String("script").hash()) {
    Array<Component*> components = level_->components("script");
    
    for (Component* component : components) {
      String scriptType = component->attr("script").string();
      if (component->label() == label && component->typeHash() == scriptType.hash()) {
        return component->attr(key);
      }
    }
  }

  Component* component = level_->component(type, label);
  return component->attr(key);
}

int AttributeScriptHandler::lua_setAttr(lua_State* l) {
  lua_pushstring(l, "attr");
  lua_gettable(l, LUA_REGISTRYINDEX);
  
  AttributeScriptHandler* handler = (AttributeScriptHandler*)lua_touserdata(l, -1);
  lua_pop(l, 1);
  
  Value value = lua_tovalue(l, -1);
  lua_pop(l, 1);
  
  String attr = lua_tostring(l, -1);
  lua_pop(l, 1);

  lua_getfield(l, -1, "type");
  String type = lua_tostring(l, -1);
  lua_pop(l, 1);
  
  lua_getfield(l, -1, "label");
  int label = lua_tointeger(l, -1);
  lua_pop(l, 1);
    
  handler->setAttr(attr, value, label, type);
  
  return 0;
}

void AttributeScriptHandler::setAttr(const String& key, const Value& value, int label, const String& type) {  
  
  if (type.hash() == String("script").hash()) {
    Array<Component*> components = level_->components("script");
    
    for (Component* component : components) {
      String scriptType = component->attr("script").string();
      if (component->label() == label && component->typeHash() == scriptType.hash()) {
        component->setAttr(key, value);
        return;
      }
    }
  }

  Component* component = level_->component(type, label);
  component->setAttr(key, value);
}
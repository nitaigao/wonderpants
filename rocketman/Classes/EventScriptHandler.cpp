#include "EventScriptHandler.h"

extern "C" {
  #include "lua.h"
  #include "lualib.h"
  #include "lauxlib.h"
};

#include "Common.h"
#include "EventSystem.h"
#include "ScriptUtils.h"

EventScriptHandler::~EventScriptHandler() {
  for (auto handler : eventHandlers_) {
    eventSystem_->unsubscribeEvent(handler.first, this, &EventScriptHandler::onEvent);
  }
}

EventScriptHandler::EventScriptHandler(lua_State* state, EventSystem* eventSystem) 
  : l_(state) 
  , eventSystem_(eventSystem) {
    
  lua_newtable(l_);
  lua_pushstring(l_, "register");
  lua_pushcfunction(l_, lua_eventRegisterEvent);
  lua_settable(l_, -3);
  
  lua_pushstring(l_, "unregister");
  lua_pushcfunction(l_, lua_eventUnregisterEvent);
  lua_settable(l_, -3);
  
  lua_pushstring(l_, "post");
  lua_pushcfunction(l_, lua_eventPostEvent);
  lua_settable(l_, -3);
  
  lua_setglobal(l_, "event");
    
  lua_pushstring(l_, "event");
  lua_pushlightuserdata(l_, this);
  lua_settable(l_, LUA_REGISTRYINDEX);
}

int EventScriptHandler::lua_eventRegisterEvent(lua_State* l) {
  lua_pushstring(l, "event");
  lua_gettable(l, LUA_REGISTRYINDEX);
  
  EventScriptHandler* handler = (EventScriptHandler*)lua_touserdata(l, -1);
  lua_pop(l, 1);
  
  int handlerId = luaL_ref(l, LUA_REGISTRYINDEX);
  
  String event = lua_tostring(l, -1);
  lua_pop(l, 1);

  handler->registerEvent(event, handlerId);
  
  return 0;
}

void EventScriptHandler::registerEvent(const String &event, int handlerId) {
  eventHandlers_[event].push_back(handlerId);
  eventSystem_->subscribeEvent(event, this, &EventScriptHandler::onEvent);
}

void EventScriptHandler::onEvent(const String& event, const Array<Value>& parameters) {
  for (int handler : eventHandlers_[event]) {
    lua_rawgeti(l_, LUA_REGISTRYINDEX, handler);
    for (Value parameter : parameters) {
      lua_pushvalue(l_, parameter);
    }
    callProtected(l_, parameters.count(), 0);
  }
}

int EventScriptHandler::lua_eventUnregisterEvent(lua_State* l) {
  return 0;
}

int EventScriptHandler::lua_eventPostEvent(lua_State* l) {
  Array<Value> parameters;
  for (int i = lua_gettop(l); i > LUA_BASE_TABLE_COUNT + 1; i = lua_gettop(l)) {
    Value value = lua_tovalue(l, -1);
    lua_pop(l, 1);
    parameters.addObject(value);
  }
  
  String event = lua_tostring(l, -1);
  lua_pop(l, 1);
    
  lua_pushstring(l, "event");
  lua_gettable(l, LUA_REGISTRYINDEX);
  
  EventScriptHandler* handler = (EventScriptHandler*)lua_touserdata(l, -1);
  lua_pop(l, 1);
  
  handler->postEvent(event, parameters.reverse());
  
  return 0;
}

void EventScriptHandler::postEvent(const String& event, const Array<Value>& parameters) {
  eventSystem_->postEventWithParams(event, parameters);
}

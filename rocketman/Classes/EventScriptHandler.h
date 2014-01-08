#ifndef EventScriptHandler_H_
#define EventScriptHandler_H_

#include "Common.h"
#include "ScriptHandler.h"

class lua_State;
class EventSystem;
class Value;

class EventScriptHandler : public ScriptHandler {
    
public:
  
  ~EventScriptHandler();
  
  EventScriptHandler(lua_State* state, EventSystem* eventSystem);
  
private:
  
  static int lua_eventRegisterEvent(lua_State* l);
  void registerEvent(const String& event, int handlerId);
  
private:
  
  static int lua_eventUnregisterEvent(lua_State* l);
  
private:
  static int lua_eventPostEvent(lua_State* l);  
  void postEvent(const String& event, const Array<Value>& parameters);  
  
private:
  
  void onEvent(const String& event, const Array<Value>& parameters);
  
private:
  
  lua_State* l_;
  EventSystem* eventSystem_;
  
private:
  
  typedef std::vector<int> EventHandlerList;
  typedef std::map<String, EventHandlerList> EventHandlerDictionary;
  
  EventHandlerDictionary eventHandlers_;
  
};



#endif

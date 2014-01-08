#ifndef GlobalScriptHandler_H_
#define GlobalScriptHandler_H_

#include "ScriptHandler.h"

class lua_State;

class GlobalScriptHandler : public ScriptHandler {
  
public:
  
  GlobalScriptHandler(lua_State* state);
  
public:
  
  int require(lua_State* l);
  
protected:
  
  const char* name() { return "global"; };
  
private:
  
  static int lua_require(lua_State* l);
  
private:
  
  lua_State* state_;
  
};

#endif

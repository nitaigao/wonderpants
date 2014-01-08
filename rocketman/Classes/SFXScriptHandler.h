#ifndef SFXScriptHandler_H_
#define SFXScriptHandler_H_

#include "ScriptHandler.h"

class lua_State;

class SFXScriptHandler : public ScriptHandler {
  
public:
  
  SFXScriptHandler(lua_State* state);
  
private:
  
  static int l_playEffect(lua_State* l);
  static int l_stopEffect(lua_State* l);
  static int l_vibrate(lua_State* l);

  
};

#endif

#include "ScriptAnimationCompleteHandler.h"

extern "C" {
  #include "lua.h"
  #include "lualib.h"
  #include "lauxlib.h"
};

#include "ScriptUtils.h"

ScriptAnimationCompleteHandler* ScriptAnimationCompleteHandler::handler(lua_State* state, int functionId) {
  return new ScriptAnimationCompleteHandler(state, functionId);
}

ScriptAnimationCompleteHandler::ScriptAnimationCompleteHandler(lua_State* state, int functionId) 
  : state_(state)
  , functionId_(functionId) { }

void ScriptAnimationCompleteHandler::animationComplete() {
  lua_rawgeti(state_, LUA_REGISTRYINDEX, functionId_);
  callProtected(state_, 0, 0);
}

AnimationCompleteHandler* ScriptAnimationCompleteHandler::clone() {
  return new ScriptAnimationCompleteHandler(state_, functionId_);
}

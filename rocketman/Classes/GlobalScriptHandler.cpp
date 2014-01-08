#include "GlobalScriptHandler.h"

extern "C" {
  #include "lua.h"
  #include "lualib.h"
  #include "lauxlib.h"
};

#include "Common.h"
#include "ScriptUtils.h"

#include "CCFileUtils.h"
USING_NS_CC;

GlobalScriptHandler::GlobalScriptHandler(lua_State* state) : state_(state) {
  lua_pushcfunction(state, &GlobalScriptHandler::lua_require);
  lua_setglobal(state, "require");

  lua_pushstring(state, "global");
  lua_pushlightuserdata(state, this);
  lua_settable(state, LUA_REGISTRYINDEX);
}

int GlobalScriptHandler::require(lua_State* l) {
  const char* moduleNameRaw = lua_tostring(l, -1);
  lua_pop(l, 1);
  
  String filename = String::withFormat("%s.luac", moduleNameRaw);
  String path = CCFileUtils::fullPathFromRelativePath(filename.c_str());
  
  loadScript_(state_, path.c_str());
    
  return 0;
}

int GlobalScriptHandler::lua_require(lua_State* l) {
  lua_pushstring(l, "global");
  lua_gettable(l, LUA_REGISTRYINDEX);
  
  GlobalScriptHandler* handler = (GlobalScriptHandler*)lua_touserdata(l, -1);
  lua_pop(l, 1);
  return handler->require(l);
}

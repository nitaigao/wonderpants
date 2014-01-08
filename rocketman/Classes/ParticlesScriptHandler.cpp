#include "ParticlesScriptHandler.h"

#include "Common.h"
#include "ScriptUtils.h"
#include "IGameView.h"

extern "C" {
  #include "lua.h"
  #include "lualib.h"
  #include "lauxlib.h"
};

ParticlesScriptHandler::ParticlesScriptHandler(lua_State* state, IGameView* view) 
  : view_(view) {
  
  lua_newtable(state);
  lua_pushstring(state, "emit");
  lua_pushcfunction(state, l_emit);
  lua_settable(state, -3);
  
  lua_pushstring(state, "stop");
  lua_pushcfunction(state, l_stop);
  lua_settable(state, -3);
  
  lua_setglobal(state, "particles");
  
  lua_pushstring(state, "particles");
  lua_pushlightuserdata(state, this);
  lua_settable(state, LUA_REGISTRYINDEX);
}

int ParticlesScriptHandler::l_emit(lua_State* l) {
  int x =  0;
  int y = 0;
  
  if (lua_gettop(l) == 5) {    
    y = lua_tonumber(l, -1);
    lua_pop(l, 1);
    
    x = lua_tonumber(l, -1);
    lua_pop(l, 1);
  }
  
  int label = lua_tonumber(l, -1);
  lua_pop(l, 1);
  
  String name = lua_tostring(l, -1);
  lua_pop(l, 1);
  
  handler<ParticlesScriptHandler>(l, "particles")->emit(x, y, name, label);
  
  return 0;
}

void ParticlesScriptHandler::emit(int x, int y, const String& name, int label) {
  view_->emitParticle(x, y, name, label);
}

int ParticlesScriptHandler::l_stop(lua_State* l) {
  int label = lua_tonumber(l, LUA_STACK_TOP);
  lua_pop(l, 1);
  
  String name = lua_tostring(l, LUA_STACK_TOP);
  lua_pop(l, 1);
  
  handler<ParticlesScriptHandler>(l, "particles")->stop(name, label);

  return 0;
}

void ParticlesScriptHandler::stop(const String &name, int label) {
  view_->stopParticle(name, label);
}

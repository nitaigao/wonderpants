#include "SFXScriptHandler.h"

extern "C" {
  #include "lua.h"
  #include "lualib.h"
  #include "lauxlib.h"
};

#include "Common.h"

#include "SoundSystem.h"

SFXScriptHandler::SFXScriptHandler(lua_State* state) {
  lua_newtable(state);
  lua_pushstring(state, "play_effect");
  lua_pushcfunction(state, l_playEffect);
  lua_settable(state, -3);
  
  lua_pushstring(state, "stop_effect");
  lua_pushcfunction(state, l_stopEffect);
  lua_settable(state, -3);
  
  lua_pushstring(state, "vibrate");
  lua_pushcfunction(state, l_vibrate);
  lua_settable(state, -3);
  
  lua_setglobal(state, "sfx");
}

int SFXScriptHandler::l_playEffect(lua_State* l) {
  String effect = lua_tostring(l, -1);
  SoundSystem::sharedSoundSystem()->playEffect(effect);  
  return 0;
}

int SFXScriptHandler::l_stopEffect(lua_State* l) {
  String effect = lua_tostring(l, -1);
  SoundSystem::sharedSoundSystem()->stopEffect(effect);
  return 0;
}

int SFXScriptHandler::l_vibrate(lua_State* l) {
  SoundSystem::sharedSoundSystem()->vibrate();
  return 0;
}


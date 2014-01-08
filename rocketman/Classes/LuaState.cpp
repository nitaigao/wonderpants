#include "LuaState.h"

#include "cocos2d.h"
USING_NS_CC;

#include "Common.h"
#include "ResourceCache.h"
#include "ScriptUtils.h"
#include "Value.h"

#include "GameState.h"
#include "GlobalScriptHandler.h"
#include "AttributeScriptHandler.h"
#include "EventScriptHandler.h"
#include "PhysicsScriptHandler.h"
#include "ComponentScriptHandler.h"
#include "GameplayScriptHandler.h"
#include "ParticlesScriptHandler.h"
#include "RendererScriptHandler.h"
#include "SFXScriptHandler.h"
#include "TransformScriptHandler.h"
#include "EntityScriptHandler.h"

extern "C" {
  #include "lua.h"
  #include "lualib.h"
  #include "lauxlib.h"
};

LuaState::LuaState(lua_State* l) : l_(l), isMarkedForDeletion_(false) {
  luaopen_base(l_); 
  luaopen_math(l_);
  luaopen_os(l_);
  luaopen_table(l_);

  luaL_loadbuffer(l_, 0, 0, 0);
  lua_pcall(l_, 0, 0, 0);
}

LuaState::~LuaState() {
  for (ScriptHandler* handler : handlers_) {
    SAFE_DELETE(handler);
  }
  
  lua_close(l_);
}

void LuaState::setGameState(lua_State* l_) {  
  lua_newtable(l_);
  lua_pushstring(l_, "STATE_LEVEL_START");
  lua_pushnumber(l_, STATE_LEVEL_START);
  lua_settable(l_, -3);
  
  lua_pushstring(l_, "STATE_IN_PLAY");
  lua_pushnumber(l_, STATE_IN_PLAY);
  lua_settable(l_, -3);
  
  lua_pushstring(l_, "STATE_LEVEL_WIN");
  lua_pushnumber(l_, STATE_LEVEL_WIN);
  lua_settable(l_, -3);
  
  lua_pushstring(l_, "STATE_LEVEL_LOST");
  lua_pushnumber(l_, STATE_LEVEL_LOST);
  lua_settable(l_, -3);
  
  lua_pushstring(l_, "STATE_GAME_COMPLETE");
  lua_pushnumber(l_, STATE_GAME_COMPLETE);
  lua_settable(l_, -3);
  
  lua_setglobal(l_, "GameState");
}

void LuaState::addScriptHandler(ScriptHandler* handler) {
  handlers_.addObject(handler);
}

LuaState* LuaState::state(Component* component, EventSystem* eventSystem, Level* level, IGameUI* ui, IGameView* view, Physics* physics, PlayerState* playerState) {
  lua_State* l = lua_open();
  LuaState* state = new LuaState(l);
  state->addScriptHandler(new GlobalScriptHandler(l));
  state->addScriptHandler(new AttributeScriptHandler(l, component, level));
  state->addScriptHandler(new EventScriptHandler(l, eventSystem));
  state->addScriptHandler(new PhysicsScriptHandler(l, physics, component));
  state->addScriptHandler(new ComponentScriptHandler(l, component, level));
  state->addScriptHandler(new GameplayScriptHandler(l, ui, view, playerState, physics));
  state->addScriptHandler(new ParticlesScriptHandler(l, view));
  state->addScriptHandler(new RendererScriptHandler(l, component, view));
  state->addScriptHandler(new SFXScriptHandler(l));
  state->addScriptHandler(new TransformScriptHandler(l, component, physics));
  state->addScriptHandler(new EntityScriptHandler(l, component, level));
  return state;
}

void LuaState::setup() {
  setGameState(l_);
}

void LuaState::loadScript(const String& path) {
  loadScript_(l_, path.c_str());
}

void LuaState::setGlobal(const String& key, const Value& value) {
  lua_pushvalue(l_, value);
  lua_setglobal(l_, key.c_str());
}

void LuaState::setTable(const String& table, const String& key, const Value& value) {  
  {
    lua_getglobal(l_, table.c_str());
    if (lua_isnil(l_, -1)) {
      lua_newtable(l_);
      lua_setglobal(l_, table.c_str());
    }
    lua_pop(l_, 1);
  }

  {
    lua_getglobal(l_, table.c_str());
    lua_pushstring(l_, key.c_str());
    lua_pushvalue(l_, value);
    lua_settable(l_, -3);
    lua_pop(l_, 1);
  }
}

void LuaState::run() {
  lua_getglobal(l_, "main");
  bool mainResult = lua_isfunction(l_, -1);
  if (mainResult) {
    callProtected(l_, 0, 0);  
  }
  else {
    lua_pop(l_, 1);
  }
}

void LuaState::update(float dt) {
  lua_getglobal(l_, "update");
  if (lua_isfunction(l_, -1)) {
    lua_pushnumber(l_, dt);
    callProtected(l_, 1, 0);  
  } else {
    lua_pop(l_, 1);
  }
}
#include "GameplayScriptHandler.h"

extern "C" {
  #include "lua.h"
  #include "lualib.h"
  #include "lauxlib.h"
};

#include "cocos2d.h"
USING_NS_CC;

#include "IGameUI.h"
#include "IGameView.h"
#include "PlayerState.h"
#include "Physics.h"

#include "ScriptUtils.h"

GameplayScriptHandler::GameplayScriptHandler(lua_State* state, IGameUI* ui, IGameView* view, PlayerState* playerState, Physics* physics) 
  : ui_(ui)
  , view_(view)
  , playerState_(playerState)
  , physics_(physics) {
    
  lua_newtable(state);
  
  lua_pushstring(state, "spawn_floaty_score");
  lua_pushcfunction(state, lua_spawnFloatyScore);
  lua_settable(state, -3);
  
  lua_pushstring(state, "remove_bonus");
  lua_pushcfunction(state, lua_playRemoveBonus);
  lua_settable(state, -3);
  
  lua_pushstring(state, "add_bonus");
  lua_pushcfunction(state, lua_addBonus);
  lua_settable(state, -3);
  
  lua_pushstring(state, "set_boost");
  lua_pushcfunction(state, lua_setBoost);
  lua_settable(state, -3);
  
  lua_pushstring(state, "spawn_swing_circle");
  lua_pushcfunction(state, lua_spawnSwingCircle);
  lua_settable(state, -3);
  
  lua_pushstring(state, "pan_to_level_fail");
  lua_pushcfunction(state, lua_panToLevelFail);
  lua_settable(state, -3);
  
  lua_pushstring(state, "is_mission_mode");
  lua_pushcfunction(state, lua_isMissionMode);
  lua_settable(state, -3);
    
  lua_pushstring(state, "create_rope");
  lua_pushcfunction(state, lua_CreateRope);
  lua_settable(state, -3);
  
  lua_pushstring(state, "delete_rope");
  lua_pushcfunction(state, lua_DeleteRope);
  lua_settable(state, -3);

  
  lua_setglobal(state, "gameplay");
  
  lua_pushstring(state, "gameplay");
  lua_pushlightuserdata(state, this);
  lua_settable(state, LUA_REGISTRYINDEX);
}

int GameplayScriptHandler::lua_spawnFloatyScore(lua_State* l) {
  
  int score = lua_tonumber(l, -1);
  lua_pop(l, 1);
  
#pragma depracated
  lua_tocolor(l, -1); // obsolete - remove
  lua_pop(l, 1);
  
  CCPoint position = lua_tovector(l, -1);
  lua_pop(l, 1);

  handler<GameplayScriptHandler>(l, "gameplay")->spawnFloatyScore(position.x, position.y, score);
  
  return 0;
}

void GameplayScriptHandler::spawnFloatyScore(int x, int y, int score) {
  view_->addFloatingLabel(x, y, score);
}

int GameplayScriptHandler::lua_playRemoveBonus(lua_State* l) {
  int bonus = lua_tonumber(l, -1);
  lua_pop(l, 1);
  
  handler<GameplayScriptHandler>(l, "gameplay")->removeBonus(bonus);

  return 0;
}

void GameplayScriptHandler::removeBonus(int bonus) {
  playerState_->removeBonus(bonus);
}

int GameplayScriptHandler::lua_addBonus(lua_State* l) {  
  int bonus = lua_tonumber(l, -1);
  lua_pop(l, 1);
  
  handler<GameplayScriptHandler>(l, "gameplay")->addBonus(bonus);

  return 0;
}

void GameplayScriptHandler::addBonus(int bonus) {
  playerState_->addBonus(bonus);
}

int GameplayScriptHandler::lua_setBoost(lua_State* l) {
  float boost = lua_tonumber(l, -1);
  lua_pop(l, 1);
  
  lua_pushstring(l, "gameplay");
  lua_gettable(l, LUA_REGISTRYINDEX);
  
  GameplayScriptHandler* handler = (GameplayScriptHandler*)lua_touserdata(l, -1);
  lua_pop(l, 1);
  
  handler->setBoost(boost);

  return 0;
}

void GameplayScriptHandler::setBoost(float boost) {
  ui_->setBoost(boost);
}

int GameplayScriptHandler::lua_spawnSwingCircle(lua_State* l) {
  int label = lua_tointeger(l, -1);
  lua_pop(l, 1);
  
  int y = lua_tointeger(l, -1);
  lua_pop(l,1);
  
  int x = lua_tointeger(l, -1);
  lua_pop(l,1);
  
  float radius = lua_tonumber(l,-1);
  lua_pop(l,1);
    
  handler<GameplayScriptHandler>(l, "gameplay")->spawnSwingCircle(x, y, radius, label);

  return 0;
}

void GameplayScriptHandler::spawnSwingCircle(int x, int y, int radius, int label) {
  view_->addCircle(x, y, radius, label);
}

int GameplayScriptHandler::lua_panToLevelFail(lua_State* l) {
  lua_pushstring(l, "gameplay");
  lua_gettable(l, LUA_REGISTRYINDEX);
  
  GameplayScriptHandler* handler = (GameplayScriptHandler*)lua_touserdata(l, -1);
  lua_pop(l, 1);
  
  handler->panToLevelFail();

  return 0;
}

void GameplayScriptHandler::panToLevelFail() {
  view_->panSceneY(70);
}

int GameplayScriptHandler::lua_isMissionMode(lua_State* l) {
  return 0;
}

int GameplayScriptHandler::lua_CreateRope(lua_State* l) {
  int to = lua_tonumber(l, LUA_STACK_TOP);
  lua_pop(l, 1);
  
  int from = lua_tonumber(l, LUA_STACK_TOP);
  lua_pop(l, 1);
  
  handler<GameplayScriptHandler>(l, "gameplay")->createRope(from, to);
  
  return 0;
}

void GameplayScriptHandler::createRope(int from, int to) {
  physics_->createRope(from, to);
  view_->createRope(from, to);
}

int GameplayScriptHandler::lua_DeleteRope(lua_State* l) {
  handler<GameplayScriptHandler>(l, "gameplay")->deleteRope();
  return 0;
}

void GameplayScriptHandler::deleteRope() {
  physics_->deleteRope();
  view_->deleteRope();
}


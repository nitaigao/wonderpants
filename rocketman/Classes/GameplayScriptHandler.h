#ifndef GameplayScriptHandler_H_
#define GameplayScriptHandler_H_

#include "ScriptHandler.h"

class lua_State;
class IGameUI;
class IGameView;
class PlayerState;
class Physics;

#include "cocos2d.h"
USING_NS_CC;

class GameplayScriptHandler : public ScriptHandler {
  
public:
  
  GameplayScriptHandler(lua_State* state, IGameUI* ui, IGameView* view, PlayerState* playerState, Physics* physics);
  
private:
  
  static int lua_setBoost(lua_State* l);
  void setBoost(float boost);
  
private:
  
  IGameUI* ui_;
  IGameView* view_;
  Physics* physics_;
  PlayerState* playerState_;
  
private:
  
  static int lua_spawnFloatyScore(lua_State* l);
  void spawnFloatyScore(int x, int y, int score);
  
  static int lua_playRemoveBonus(lua_State* l);
  void removeBonus(int bonus);
  
  static int lua_addBonus(lua_State* l);
  void addBonus(int bonus);
  
  static int lua_spawnSwingCircle(lua_State* l);
  void spawnSwingCircle(int x, int y, int radius, int label);
  
  static int lua_panToLevelFail(lua_State* l);
  void panToLevelFail();
  
  static int lua_isMissionMode(lua_State* l);
  
  static int lua_CreateRope(lua_State* l);
  void createRope(int from, int to);
  
  static int lua_DeleteRope(lua_State* l);
  void deleteRope();
  
};

#endif

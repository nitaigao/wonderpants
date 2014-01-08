#ifndef ScriptManager_H_
#define ScriptManager_H_

#include "Common.h"

#include "EntityManager.h"

class Level;
class IGameView;
class EventSystem;
class LuaState;

class ScriptManager : public EntityManager {
  
public:
  
  ~ScriptManager();
  
public:
  
  void setup(Level* level, IGameView* view, IGameUI* ui, Physics* physics, EventSystem* eventSystem, PlayerState* playerState);
  
  void update(float dt);
  
  void setupComponent(Component* component);
  
  void tearDownComponent(Component* component);
  
public:
  
  EntityManager* clone();
  
private:
  
  Level* level_;
  
  IGameView* view_;
  IGameUI* ui_;
  Physics* physics_;
  EventSystem* eventSystem_;
  PlayerState* playerState_;
  
  Array<LuaState*> states_;
  
};

#endif

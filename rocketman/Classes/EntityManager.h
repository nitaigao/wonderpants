#ifndef EntityManager_H_
#define EntityManager_H_

class Level;
class IGameView;
class IGameUI;
class Physics;
class EventSystem;
class PlayerState;
class Component;

class EntityManager {
  
public:
  
  virtual ~EntityManager() { };
  
  virtual void setup(Level* level, IGameView* view, IGameUI* ui, Physics* physics, EventSystem* eventSystem, PlayerState* playerState) = 0;
  
  virtual void setupComponent(Component* component) = 0;
  
  virtual void tearDownComponent(Component* component) = 0;
  
  virtual void update(float dt) = 0;
  
  virtual EntityManager* clone() = 0;
  
};

#endif

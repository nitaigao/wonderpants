#ifndef AnimatableManager_H_
#define AnimatableManager_H_

#include "EntityManager.h"

class AnimatableDecorator;

class AnimatableManager : public EntityManager {
  
public:
  
  void setup(Level* level, IGameView* view, IGameUI* ui, Physics* physics, EventSystem* eventSystem, PlayerState* playerState);
  
  void update(float dt);
  
  void setupComponent(Component* component);
  
  void tearDownComponent(Component* component);
  
  void setupComponents(const AnimatableDecorator& component);
  
public:
  
  EntityManager* clone();
  
private:
  
  Level* level_;
  IGameView* view_;
  
};

#endif

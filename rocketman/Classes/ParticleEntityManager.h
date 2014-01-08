#ifndef ParticleEntityManager_H_
#define ParticleEntityManager_H_

class Level;

#include "EntityManager.h"

class ParticleEntityManager : public EntityManager {
  
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
  
};

#endif

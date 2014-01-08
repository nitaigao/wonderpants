#ifndef SpatialEntityManager_H_
#define SpatialEntityManager_H_

#include "EntityManager.h"

class SpatialEntityManager : public EntityManager {
  
public:
  
  void setup(Level* level, IGameView* view, IGameUI* ui, Physics* physics, EventSystem* eventSystem, PlayerState* playerState);
  
  void setupComponent(Component* component);
  
  void tearDownComponent(Component* component);
  
  void update(float dt);
  
public:
  
  EntityManager* clone();
  
private:
  
  Level* level_;
  
};

#endif

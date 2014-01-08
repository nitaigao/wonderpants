#ifndef DefaultEntityManager_H_
#define DefaultEntityManager_H_

#include "EntityManager.h"

class DefaultEntityManager : public EntityManager {
  
public:
  
  void setup(Level* level, IGameView* view, IGameUI* ui, Physics* physics, EventSystem* eventSystem, PlayerState* playerState);
  
  void setupComponent(Component* component);
  
  void tearDownComponent(Component* component);
  
  void update(float dt);
  
  EntityManager* clone();

  
};

#endif

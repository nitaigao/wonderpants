#ifndef PhysicalEntityManager_H_
#define PhysicalEntityManager_H_

#include "EntityManager.h"

class Physics;
class Level;

class PhysicalEntityManager : public EntityManager {
  
  
public:
  
  void setup(Level* level, IGameView* view, IGameUI* ui, Physics* physics, EventSystem* eventSystem, PlayerState* playerState);
  
  void update(float dt);
  
  void setupComponent(Component* component);
  
  void tearDownComponent(Component* component);
  
  EntityManager* clone();
  
private:
  
  Level* level_;
  Physics* physics_;
  
  
};

#endif

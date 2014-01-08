#include "DefaultEntityManager.h"

void DefaultEntityManager::setup(Level* level, IGameView* view, IGameUI* ui, Physics* physics, EventSystem* eventSystem, PlayerState* playerState) {
  
}

void DefaultEntityManager::setupComponent(Component* component) {
  
}

void DefaultEntityManager::update(float dt) {
  
}

void DefaultEntityManager::tearDownComponent(Component* component) {
  
}

EntityManager* DefaultEntityManager::clone() { 
  return new DefaultEntityManager();
}
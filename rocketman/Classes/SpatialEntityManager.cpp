#include "SpatialEntityManager.h"

#include "Common.h"

#include "Level.h"
#include "Component.h"

EntityManager* SpatialEntityManager::clone() {
  return new SpatialEntityManager();
}

void SpatialEntityManager::setup(Level* level, IGameView* view, IGameUI* ui, Physics* physics, EventSystem* eventSystem, PlayerState* playerState) {
  level_ = level;
}

void SpatialEntityManager::update(float dt) {
  Array<Component*> components = level_->components("spatial");
  for (Component* component : components) {
    component->setAttr("last_x", component->attr("x").intValue());
    component->setAttr("last_y", component->attr("y").intValue());
    component->setAttr("last_rotation", component->attr("rotation").intValue());
  }
}

void SpatialEntityManager::setupComponent(Component* component) {
  
}

void SpatialEntityManager::tearDownComponent(Component *component) {
  
}
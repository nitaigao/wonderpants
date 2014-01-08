#include "Level.h"

#include "Common.h"

#include "Entity.h"
#include "Component.h"

#include "EntityManager.h"

#include "DefaultEntityManager.h"
#include "IGameView.h"

#include "DefaultEntityManager.h"
#include "SpatialEntityManager.h"
#include "VisibleEntityManager.h"
#include "AnimatableManager.h"
#include "ScriptManager.h"
#include "PhysicalEntityManager.h"
#include "ParticleEntityManager.h"

Level* Level::clone() {
  Level* level = new Level();
  
  for (const String& tutorial : tutorials_) {
    level->addTutorial(tutorial);
  }
  
  level->tutorials_ = Array<String>(tutorials_);
  
  for (Component* component : components_) {
    Component* newComponent = component->clone();
    level->addComponent(newComponent);
  }
  
  for (auto entityManagerPair : entityManagers_) {
    EntityManager* entityManager = entityManagerPair.second->clone();
    level->entityManagers_[entityManagerPair.first] = entityManager;
  }
  
  level->lastEntityLabel = lastEntityLabel;
  
  return level;
}

Level::~Level() {  
  for (auto managerPair : entityManagers_) {
    SAFE_DELETE(managerPair.second);
  }
  
  for (auto componentPair : componentsByLabel_) {
    SAFE_DELETE(componentPair.second);
  }
  
  for (auto componentPair : componentsByType_) {
    SAFE_DELETE(componentPair.second);
  }
  
  for (Component* component : components_) {
    SAFE_DELETE(component);
  }  
}

Level::Level() : lastEntityLabel(0) {
}

Level* Level::level() {
  Level* level = new Level();
  level->addEntityManager("default", new DefaultEntityManager);
  level->addEntityManager("spatial", new SpatialEntityManager);
  level->addEntityManager("visible", new VisibleEntityManager);
  level->addEntityManager("animatable", new AnimatableManager);
  level->addEntityManager("script", new ScriptManager);
  level->addEntityManager("physical", new PhysicalEntityManager);
  level->addEntityManager("particle", new ParticleEntityManager);
  return level;
}

void Level::addEntityManager(const String& type, EntityManager* manager) {
  entityManagers_[type] = manager;
}

void Level::addTutorial(const String& tutorial) {
  tutorials_.addObject(tutorial);
}

int Level::addEntity(Entity* entity) {  
  Array<Component*> components = entity->components();
  for (Component* component : components) {
    component->setLabel(lastEntityLabel);
    addComponent(component);
  }
  return lastEntityLabel++;
}

void Level::addComponent(Component *component) {
  components_.addObject(component);
  
  if (componentsByLabel_.find(component->label()) == componentsByLabel_.end()) {
    componentsByLabel_[component->label()] = new Array<Component*>();
  }
  componentsByLabel_[component->label()]->addObject(component);
  
  if (componentsByType_.find(component->typeHash()) == componentsByType_.end()) {
    componentsByType_[component->typeHash()] = new Array<Component*>();
  }
  componentsByType_[component->typeHash()]->addObject(component);
}

void Level::setup(int attempts, IGameView* view, IGameUI* ui, Physics* physics, EventSystem* eventSystem, PlayerState* playerState) {
  if (!attempts && tutorials_.count()) {
    view->addTutorials(tutorials_);
  }
  
  for (auto manager : entityManagers_) {
    manager.second->setup(this, view, ui, physics, eventSystem, playerState);
  }
}

EntityManager* Level::managerForType(const String& type) {
  if (entityManagers_.find(type) != entityManagers_.end()) { 
    return entityManagers_[type];
  }
  return entityManagers_["default"];
}

void Level::setupComponents(int label) {
  Array<Component*>* existingComponents = componentsByLabel_[label];
  Array<Component*> components = Array<Component*>::fromArray(*existingComponents);
  
  for (Component* component : components) {
    EntityManager* manager = managerForType(component->type());
    manager->setupComponent(component);
  }
}

Array<Component*> Level::components(const String& type) {
  if (componentsByType_.find(type.hash()) == componentsByType_.end()) {
    return std::vector<Component*>();
  }
  auto components = *componentsByType_[type.hash()];
  return components;
}

Component* Level::component(const String& type, int label) {
  auto components = *componentsByLabel_[label];
  
  unsigned long hash = type.hash();
  for (Component* component : components) {
    if (component->typeHash() == hash) {
      return component;
    }
  }

  return 0;
}

void Level::update(float dt) {
  for (auto manager : entityManagers_) {
    manager.second->update(dt);
  }
} 

void Level::destroyComponents(int label) {
  auto components = *componentsByLabel_[label];
  
  for (Component* component : components) {    
    for (auto manager : entityManagers_) {
      manager.second->tearDownComponent(component);
    }      
    removeComponent(component);
    SAFE_DELETE(component);
  }
}

void Level::removeComponent(Component* component) {
  components_.removeObject(component);
  
  auto componentsByLabel = componentsByLabel_[component->label()];
  componentsByLabel->removeObject(component);

  auto componentsByType = componentsByType_[component->typeHash()];
  componentsByType->removeObject(component);
}

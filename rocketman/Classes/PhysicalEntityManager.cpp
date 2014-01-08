#include "PhysicalEntityManager.h"

#include "Component.h"
#include "Level.h"
#include "Physics.h"
#include "SpatialDecorator.h"

static const char* PHYSICAL_TYPE = "physical";
static const char* SPATIAL_TYPE = "spatial";

static const char* PHYSICAL_ATTR_DATA = "data";
static const char* PHYSICAL_ATTR_SIM = "sim";
static const char* PHYSICAL_ATTR_ALWAYS_AWAKE = "always_awake";
static const char* PHYSICAL_ATTR_GRAVITY = "gravity";
static const char* PHYSICAL_ATTR_BULLET = "bullet";

EntityManager* PhysicalEntityManager::clone() {
  return new PhysicalEntityManager();
}

void PhysicalEntityManager::setup(Level* level, IGameView* view, IGameUI* ui, Physics* physics, EventSystem* eventSystem, PlayerState* playerState) {
  
  physics_ = physics;
  level_ = level;
  
  Array<Component*> physicals = level->components(PHYSICAL_TYPE);
  
  for (Component* physical : physicals) {
    setupComponent(physical);
  }
}

void PhysicalEntityManager::update(float dt) {
  Array<Component*> physicals = level_->components(PHYSICAL_TYPE);
  
  for (Component* physical : physicals) {
    if (physical->isMarkedForDeletion()) {
      physics_->removeObject(physical->label());
      level_->removeComponent(physical);
    }
  }
}

void PhysicalEntityManager::setupComponent(Component* physical) {
  Component* spatialComponent = level_->component(SPATIAL_TYPE, physical->label());
  SpatialDecorator spatial(spatialComponent);
  
  String data = physical->attr(PHYSICAL_ATTR_DATA).string();
  String sim = physical->attr(PHYSICAL_ATTR_SIM).string();
  
  bool allowSleep = !physical->attr(PHYSICAL_ATTR_ALWAYS_AWAKE).boolValue();
  bool gravity = true;
  if (!physical->attr(PHYSICAL_ATTR_GRAVITY).isNull()) {
    gravity = physical->attr(PHYSICAL_ATTR_GRAVITY).boolValue();
  }
  
  physical->attr(PHYSICAL_ATTR_GRAVITY).boolValue();
  bool isBullet = physical->attr(PHYSICAL_ATTR_BULLET).boolValue();
  
  physics_->addObject(spatial.x(), spatial.y(), spatial.rotation(), data, sim, allowSleep, gravity, isBullet, physical->label(), spatialComponent); 
}

void PhysicalEntityManager::tearDownComponent(Component *component) {
  physics_->removeObject(component->label());
}
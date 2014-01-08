#include "VisibleEntityManager.h"

#include "Common.h"

#include "Component.h"
#include "Value.h"
#include "Level.h"
#include "GameView.h"
#include "SpatialDecorator.h"

static String VISIBLE_TYPE = "visible";
static String VISIBLE_KEY_ASSET = "asset";
static String VISIBLE_KEY_Z = "z";
static String VISIBLE_KEY_VISIBLE = "visible";


static String SPATIAL_TYPE = "spatial";
static String SPATIAL_KEY_X = "x";
static String SPATIAL_KEY_Y = "y";
static String SPATIAL_KEY_ROTATION = "rotation";

EntityManager* VisibleEntityManager::clone() {
  return new VisibleEntityManager();
}

void VisibleEntityManager::setup(Level* level, IGameView* view, IGameUI* ui, Physics* physics, EventSystem* eventSystem, PlayerState* playerState) {
  level_ = level;
  view_ = view;
  
  Array<Component*> visibles = level->components(VISIBLE_TYPE);
  
  for (Component* visible : visibles) {
    setupComponent(visible);
  }
}

void VisibleEntityManager::setupComponent(Component* visible) {
  String asset = visible->attr(VISIBLE_KEY_ASSET).string();
  int z = visible->attr(VISIBLE_KEY_Z).intValue();
  
    
  bool isVisible = true;
  if (!visible->attr(VISIBLE_KEY_VISIBLE).isNull()) {
    isVisible = visible->attr(VISIBLE_KEY_VISIBLE).boolValue();
  }
  
  Component* spatialComponent = level_->component(SPATIAL_TYPE, visible->label());
  SpatialDecorator spatial(level_->component("spatial", visible->label()));
  view_->addSprite(asset, spatial.x(), spatial.y(), z, spatial.rotation(), visible->label(), spatialComponent, isVisible);  
}

void VisibleEntityManager::update(float dt) {
  Array<Component*> visibles = level_->components(VISIBLE_TYPE);
  
  for (Component* visible : visibles) {
    if (visible->isMarkedForDeletion()) {
      view_->removeSprite(visible->label());
      level_->removeComponent(visible);
    }
  }
}

void VisibleEntityManager::tearDownComponent(Component *component) {
  view_->removeSprite(component->label());
}
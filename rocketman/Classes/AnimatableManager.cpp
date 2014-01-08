#include "AnimatableManager.h"

#include "Common.h"

#include "Level.h"
#include "Component.h"
#include "IGameView.h"
#include "DefaultAnimationCompleteHandler.h"

#include "SpatialDecorator.h"
#include "AnimatableDecorator.h"

#include "cocos2d.h"
USING_NS_CC;

static String ANIMATABLE_TYPE = "animable";

EntityManager* AnimatableManager::clone() {
  return new AnimatableManager();
}

void AnimatableManager::setup(Level* level, IGameView* view, IGameUI* ui, Physics* physics, EventSystem* eventSystem, PlayerState* playerState) {

  level_ = level;
  view_ = view;
  
  Array<Component*> animatables = level->components(ANIMATABLE_TYPE);
  
  for (Component* animatable : animatables) {
    setupComponent(animatable);
  }
}

void AnimatableManager::update(float dt) {
  Array<Component*> animables = level_->components(ANIMATABLE_TYPE);
  
  for (Component* animable : animables) {
    if (animable->isMarkedForDeletion()) {
      view_->removeSprite(animable->label());
      level_->removeComponent(animable);
    }
  } 
}

void AnimatableManager::setupComponent(Component* component) {
  setupComponents(component);
}

void AnimatableManager::setupComponents(const AnimatableDecorator &animatable) {
  animatable.cacheAnimations();
  SpatialDecorator spatial(level_->component("spatial", animatable.label()));
  view_->addSprite(animatable.defaultFrame(), spatial.x(), spatial.y(), animatable.z(), spatial.rotation(), animatable.label(), level_->component("spatial", animatable.label()), true);
  view_->playAnimation(animatable.defaultAnimation(), animatable.label(), true, true, DefaultAnimationCompleteHandler::handler()); 
}

void AnimatableManager::tearDownComponent(Component *component) {
  view_->removeSprite(component->label());
}
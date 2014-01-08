#include "AnimatableDecorator.h"

#include "Component.h"
#include "Value.h"

#include "cocos2d.h"
USING_NS_CC;

AnimatableDecorator::AnimatableDecorator(Component* component) : component_(component) { 
  
}

int AnimatableDecorator::z() const {
  return component_->attr("z").intValue();
}

Array<Value> AnimatableDecorator::animations() const {
  return component_->attr("animations").arrayValue();
}

String AnimatableDecorator::defaultAnimation() const {
  return component_->attr("default").string();
}

String AnimatableDecorator::defaultFrame() const {
  String defaultFrame;
  for (Value animationValue : animations()) {      
    {
      if (defaultAnimation() == animationValue.mapValue()["name"].string()) {
        defaultFrame = animationValue.mapValue()["frames"].arrayValue().first().string();
      }
    }
  }
  return defaultFrame;
}

void AnimatableDecorator::cacheAnimations() const {
  for (Value animationValue : animations()) {      
    {
      Array<Value> frames = animationValue.mapValue()["frames"].arrayValue();
      
      CCMutableArray<CCSpriteFrame*>* spriteFrames = new CCMutableArray<CCSpriteFrame*>();
      spriteFrames->autorelease();
      
      for (Value frame : frames) {
        CCSpriteFrame* spriteFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(frame.string().c_str());
        spriteFrames->addObject(spriteFrame);
      }
      
      float delay = animationValue.mapValue()["delay"].floatValue();
      CCAnimation* animation = CCAnimation::animationWithFrames(spriteFrames, delay);
      CCAnimationCache::sharedAnimationCache()->addAnimation(animation, animationValue.mapValue()["name"].string().c_str());
    }
  }
}

int AnimatableDecorator::label() const {
  return component_->label();
}
#include "Input.h"

#include "cocos2d.h"
USING_NS_CC;

#include "EventSystem.h"
#include "Common.h"
#include "Value.h"

static const char* SCREEN_ORIENTATION = "SCREEN_ORIENTATION";

Input* Input::node(EventSystem* eventSystem) {
  Input* node = new Input(eventSystem);
  node->autorelease();
  return node;
}

Input::Input(EventSystem* eventSystem) 
  : eventSystem_(eventSystem)
  , isPaused_(false)
  , frameTime_(0) {
    CCTouchDispatcher::sharedDispatcher()->addTargetedDelegate(this, 0, false);
    CCAccelerometer::sharedAccelerometer()->addDelegate(this);
    
    orientation_ = (ccDeviceOrientation)CCUserDefault::sharedUserDefault()->getIntegerForKey(SCREEN_ORIENTATION);
}

Input::~Input() {
  CCTouchDispatcher::sharedDispatcher()->removeDelegate(this);
  CCAccelerometer::sharedAccelerometer()->removeDelegate(this);
}

void Input::onEnter() {
  CCNode::onEnter();
  scheduleUpdate();
}

void Input::pause() {
  isPaused_ = true;
}

void Input::resume() {
  isPaused_ = false;
}

bool Input::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent) {
  eventSystem_->postEvent("input_started");  
  return true;
}

void Input::ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent) {
  
}

void Input::ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent) {
  eventSystem_->postEvent("input_ended");  
}

cocos2d::CCPoint normalizeAcceleration(const cocos2d::CCPoint& acceleration) {
  float accelX = acceleration.y < 0 ? -acceleration.y : acceleration.y;
  float deltaX = 1 - clampf(accelX, 0, 1);
  return CCPointMake(acceleration.x, deltaX);
}

void Input::didAccelerate(cocos2d::CCAcceleration* pAccelerationValue) {
  if (!isPaused_) {
    isPaused_ = true;
    CCPoint filteredAcceleration = filter_.addAcceleration(pAccelerationValue->x, pAccelerationValue->y);
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    filteredAcceleration = CCPointMake(-filteredAcceleration.y, filteredAcceleration.x);
#endif
    
    CCPoint normalizedAcceleration = normalizeAcceleration(filteredAcceleration);
    
    float deadZone = 0.1f;
    if (normalizedAcceleration.x < -deadZone || normalizedAcceleration.x > deadZone) {
      String direction = normalizedAcceleration.x < 0 ? "left" : "right";      
      eventSystem_->postEvent("input_moved", direction, normalizedAcceleration.y);
    }  
  }
}

void Input::update(float dt) {
  frameTime_ += dt;
  
  // cap the accelerometer frequency to 30hz
  if (frameTime_ >= 1.0f/30.0f) { 
    frameTime_ = 0;
    isPaused_ = false;
  }
}
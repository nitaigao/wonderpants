#ifndef Input_H_
#define Input_H_

#include "CCNode.h"
#include "CCTouchDelegateProtocol.h"
#include "CCAccelerometerDelegate.h"
#include "LowPassAccelerometerFilter.h"

namespace cocos2d {
  class CCTouch;
  class CCEvent;
}

class EventSystem;

class Input : public cocos2d::CCNode, public cocos2d::CCTouchDelegate, public cocos2d::CCAccelerometerDelegate {
  
public:
  
  static Input* node(EventSystem* eventSystem);
  
public:
  
  ~Input();

public:
  
  void pause();
  void resume();
  
public:
  
  bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
  void ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
  void ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
  
public:
  
  void didAccelerate(cocos2d::CCAcceleration* pAccelerationValue);
  
  void onEnter();
  
public:
  
  void update(float dt);
  
private:
  
  Input(EventSystem* eventSystem);
  
private:
  
  EventSystem* eventSystem_;
  bool isPaused_;
  LowPassAccelerometerFilter filter_;
  cocos2d::ccDeviceOrientation orientation_;
  float frameTime_;
  
};

#endif

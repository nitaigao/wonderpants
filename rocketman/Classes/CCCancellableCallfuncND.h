#ifndef CCCancellableCallfuncND_H_
#define CCCancellableCallfuncND_H_

#include "cocos2d.h"

class AnimationCompleteHandler;

class CCCancellableCallfuncND : public cocos2d::CCActionInstant {
  
public:
  
  ~CCCancellableCallfuncND();
  
  CCCancellableCallfuncND();
  
public:

  static CCCancellableCallfuncND * actionWithHandler(AnimationCompleteHandler* handler);
  
public:
  
  bool initWithHandler(AnimationCompleteHandler* handler);
  
  void startWithTarget(cocos2d::CCNode *pTarget);
  
  void execute();
  
  virtual CCObject* copyWithZone(cocos2d::CCZone* zone);
  
private:
  
  AnimationCompleteHandler* m_pData;
  
};

#endif

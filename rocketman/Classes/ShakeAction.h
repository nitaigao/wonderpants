#ifndef ShakeAction_H_
#define ShakeAction_H_

#include "cocos2d.h"
USING_NS_CC;

class ShakeAction : public cocos2d::CCFiniteTimeAction {
  
public:
  
  static ShakeAction* action(float duration, float radius);
  
  void init(float duration, float radius);
  
  void startWithTarget(CCNode* target);
  
  void step(ccTime dt);
  
  void stop();
  
  bool isDone();
  
private:
  
  ccTime time_;
  CCPoint originalPosition;
  float radius_;
  
};

#endif

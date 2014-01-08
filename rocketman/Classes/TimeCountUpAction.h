#ifndef TimeCountUpAction_H_
#define TimeCountUpAction_H_

#include "cocos2d.h"

class CCLabelBNFont;

class TimeCountUpAction : public cocos2d::CCActionInterval {
  
public:
  
  static TimeCountUpAction* actionWithCount(int count, CCLabelBNFont* target, float duration, float blipInterval);
  
public:
  
  TimeCountUpAction(int count, CCLabelBNFont* target, float duration, float blipInterval);
  
public:
  
  void update(cocos2d::ccTime time);
  
private:
  
  int count_;
  CCLabelBNFont* target_;
  float duration_;
  float blipInterval_;
  float currentCount_;
  int blipCount_;
  
};

#endif

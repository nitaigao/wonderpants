#ifndef ScoreCountUpAction_H_
#define ScoreCountUpAction_H_

#include "cocos2d.h"

class CCLabelBNFont;

class ScoreCountUpAction : public cocos2d::CCActionInterval {
  
public:
  
  static ScoreCountUpAction* actionWithCount(int count, CCLabelBNFont* target, float duration, float blipInterval);
  
public:
  
  ScoreCountUpAction(int count, CCLabelBNFont* target, float duration, float blipInterval);
  
public:
  
  void update(cocos2d::ccTime time);
  void stop();
  
private:
  
  int count_;
  CCLabelBNFont* target_;
  float duration_;
  float blipInterval_;
  float currentCount_;
  int blipCount_;
  
};

#endif

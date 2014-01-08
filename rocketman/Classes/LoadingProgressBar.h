#ifndef LoadingProgressBar_H_
#define LoadingProgressBar_H_

#include "cocos2d.h"

class LoadingProgressBar : public cocos2d::CCSprite {
  
public:
  
  static LoadingProgressBar* node();
  
public:
  
  bool init();
  
  void setProgress(float progress);
  
  cocos2d::CCSprite* createProgress(float progress);
  
};

#endif

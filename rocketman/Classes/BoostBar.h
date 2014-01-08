#ifndef BoostBar_H_
#define BoostBar_H_

#include "CCNode.h"

namespace cocos2d {
  class CCSprite;
}

class BoostBar : public cocos2d::CCNode {
  
public:
  
  static BoostBar* node();
  
  void init();
  
  void setBoost(float boost);
  
};

#endif

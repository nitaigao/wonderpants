#ifndef CCSpriteCascadeVisible_H_
#define CCSpriteCascadeVisible_H_

#include "CCSprite.h"

class CCSpriteCascadeVisible : public cocos2d::CCSprite {
  
public:
  
  static CCSpriteCascadeVisible* sprite();
  
public:
  
  void setIsVisible(bool isVisible);
  
};

#endif

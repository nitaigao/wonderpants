#ifndef ChapterLockedPriceTag_H_
#define ChapterLockedPriceTag_H_

#include "cocos2d.h"
USING_NS_CC;

class ChapterLockedPriceTag : public cocos2d::CCSprite {
  
public:
  
  static ChapterLockedPriceTag* node(int score);
  
  bool init(int score);
  
};

#endif

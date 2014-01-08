#ifndef ChapterUnlockedPriceTag_H_
#define ChapterUnlockedPriceTag_H_

#include "cocos2d.h"
USING_NS_CC;

class ChapterUnlockedPriceTag : public cocos2d::CCSprite {
  
public:

  static ChapterUnlockedPriceTag* node(int required);
  
  bool init(int required);
  
};

#endif

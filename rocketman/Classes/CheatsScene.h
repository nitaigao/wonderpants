#ifndef CheatsScene_H_
#define CheatsScene_H_

#include "cocos2d.h"

class CheatsScene : public cocos2d::CCScene {
  
public:
  
  static CheatsScene* node();
  
  bool init();
  
  void unlockChapter1();
  
  void unlockChapter2();
  
  void unlockChapter3();
  
  void back();
  
};

#endif

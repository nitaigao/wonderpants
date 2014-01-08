#ifndef TestScene_H_
#define TestScene_H_

#include "CCScene.h"

class TestScene : public cocos2d::CCScene {
  
public:
  
  static TestScene* scene();
  
  bool init();
  
  void reload();
  
};

#endif

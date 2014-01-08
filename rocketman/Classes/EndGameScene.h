#ifndef EndGameScene_H_
#define EndGameScene_H_

#include "CCScene.h"

class EndGameScene : public cocos2d::CCScene {
  
public:
  
  static EndGameScene* node(int chapter);
  
  EndGameScene(int chapter);
  
public:
  
  bool init();
  
  void showThanks();
  
private:
  
  int chapter_;
  
};

#endif

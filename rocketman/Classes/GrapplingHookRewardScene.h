#ifndef GrapplingHookRewardScene_H_
#define GrapplingHookRewardScene_H_

#include "CCScene.h"

class GrapplingHookRewardScene : public cocos2d::CCScene {
  
public:
  
  static GrapplingHookRewardScene* nodeWithChapter(int chapter, int level);
  
public:
  
  GrapplingHookRewardScene(int chapter, int level);
  
public:
  
  bool init();
  
  void continueToGame();
  
private:
  
  int chapter_;
  int level_;
  
  
};

#endif

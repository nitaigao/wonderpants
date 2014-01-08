#ifndef ParachuteRewardScene_H_
#define ParachuteRewardScene_H_

#include "CCScene.h"

class ParachuteRewardScene : public cocos2d::CCScene {
  
public:
  
  static ParachuteRewardScene* nodeWithChapter(int chapter, int level);
  
public:
  
  ParachuteRewardScene(int chapter, int level);
  
public:
  
  bool init();
  
  void continueToGame();
  
private:
  
  int chapter_;
  int level_;
  
  
};

#endif

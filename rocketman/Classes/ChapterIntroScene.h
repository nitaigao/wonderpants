#ifndef ChapterIntroScene_H_
#define ChapterIntroScene_H_

#include "CCScene.h"
#include "CCTouchDelegateProtocol.h"

class ChapterIntroScene : public cocos2d::CCScene, public cocos2d::CCTargetedTouchDelegate {
  
public:
  
  static ChapterIntroScene* nodeWithChapter(int chapter);
  
public:
  
  void init();
  
  void continueToGame();
  
  bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
  
  
private:
  
  ChapterIntroScene(int chapter);
    
private:
  
  int chapter_;
  
};

#endif

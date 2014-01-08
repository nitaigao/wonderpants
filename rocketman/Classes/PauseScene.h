#ifndef PauseScene_H_
#define PauseScene_H_

#include "Scene.h"

class GameScene;

class PauseScene : public Scene<PauseScene> {
  
  int chapter_;
  
  GameScene* controller_;
  
public:
  
  static PauseScene* sceneWithChapter(int chapter, GameScene* controller);
  
  void initWithChapter(int chapter, GameScene* controller);
  
  bool init();
  
  void levelSelect(cocos2d::CCObject* sender);
  
  void chapterSelect(cocos2d::CCObject* sender);
  
  void resumeGame(cocos2d::CCObject* sender);
  
};

#endif

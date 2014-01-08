#ifndef LevelEndView_H_
#define LevelEndView_H_

#include "cocos2d.h"

class GameScene;

class LevelEndView : public cocos2d::CCNode {
  
public:
  
  static LevelEndView* node(GameScene* controller, int chapter, int level, int coins, int time, int score);
  
  LevelEndView(GameScene* controller, int chapter, int level, int coins, int time, int score);
  
  void onEnter();
  
private:
  
  void showButtons();
  
  void showLevelsButton();
  
  void showResetButton();
  
private:
  
  void showLevel();
  
  void showCoins();
  void showCoin2();
  void showCoin3();
  void showTime();
  void showScore();
  
private:
  
  GameScene* controller_;
  int chapter_;
  int level_;
  int coins_;
  
  int coinAwardIndex_;
  int time_;
  int score_;
  
};

#endif

#ifndef GameScene_H_
#define GameScene_H_

#include "Common.h"
#include "Scene.h"

class Physics;
class EntitySystemManager;
class Level;
class EventSystem;
class Input;
class PlayerState;
class Value;

class GameScene : public cocos2d::CCScene {
  
public:
  
  static GameScene* nodeWithChapter(int chapter, int level, int attempts);
  
  GameScene();
  
  ~GameScene();
  
public:
  
  void initWithChapter(int chapter, int level, int attempts);
  
  void pauseGame(cocos2d::CCObject* sender);
  
  void restartGame(cocos2d::CCObject* sender);
  
  void resumeGame(cocos2d::CCObject* sender);
  
  void nextLevel(cocos2d::CCObject* sender);
  
  void levelSelect(cocos2d::CCObject* sender);
  
private:
  
  void draw();
  
  void update(float dt);
  
  void setupLevel(Level* level);
  
  void reloadLevel();
  
  void winLevel();
  
private:
  
  void targetableCollected(const String& event, const Array<Value>& data);
  
  void launchableCrashed(const String& event, const Array<Value>& data);
    
private:
  
  int levelIndex_;
  int chapterIndex_;
  int attempts_;
  bool isPaused_;
  Timer levelTimer_;
  Level* level_;
  EventSystem* eventSystem_;
  Physics* physics_;
  PlayerState* playerState_;
  
};

#endif

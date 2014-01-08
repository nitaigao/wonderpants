#ifndef GameLoadingScene_H_
#define GameLoadingScene_H_

#include "LoadingScene.h"

class GameLoadingScene : public LoadingScene {
  
private:
  
  int chapter_;
  int level_;

public:

  static GameLoadingScene* nodeWithChapter(int chapter, int level);
  
public:
  
  GameLoadingScene(int chapter, int level);
  
public:
  
  void setupTasks();
  
  void changeScene();
  
};

#endif

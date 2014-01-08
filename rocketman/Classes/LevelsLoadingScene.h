#ifndef LevelsLoadingScene_H_
#define LevelsLoadingScene_H_

#include "LoadingScene.h"

class LevelsLoadingScene : public LoadingScene {
  
private:
  
  int chapter_;

public:
  
  static LevelsLoadingScene* nodeWithChapter(int chapter);
  
  void initWithChapter(int chapter);
  
  void setupTasks();
  
  void changeScene();
  
};

#endif

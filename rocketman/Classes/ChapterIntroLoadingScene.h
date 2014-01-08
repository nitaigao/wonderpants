#ifndef ChapterIntroLoadingScene_H_
#define ChapterIntroLoadingScene_H_

#include "LoadingScene.h"

class ChapterIntroLoadingScene : public LoadingScene {
  
public:
  
  static ChapterIntroLoadingScene* nodeWithChapter(int chapter);
  
public:
  
  ChapterIntroLoadingScene(int chapter);
  
public:
  
  void setupTasks();
  
  void changeScene();
  
private:
  
  int chapter_;
  
  
};

#endif

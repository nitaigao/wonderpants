#ifndef ChapterUnlockedLoadingScene_H_
#define ChapterUnlockedLoadingScene_H_

#include "LoadingScene.h"

class ChapterUnlockedLoadingScene : public LoadingScene {
  
private:
  
  int chapter_;
  
public:
  
  static ChapterUnlockedLoadingScene* nodeWithChapter(int chapter);
  
  void initWithChapter(int chapter);
  
  void setupTasks();
  
  void changeScene();
  
};

#endif

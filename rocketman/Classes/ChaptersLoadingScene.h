#ifndef ChaptersLoadingScene_H_
#define ChaptersLoadingScene_H_

#include "LoadingScene.h"

class ChaptersLoadingScene : public LoadingScene {
  
private:
  
  int chapter_;
  
public:
  
  static ChaptersLoadingScene* nodeWithChapter(int chapter);
  
  void initWithChapter(int chapter);
  
  void setupTasks();
  
  void changeScene();
  
};

#endif

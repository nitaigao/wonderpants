#ifndef EndGameLoadingScene_H_
#define EndGameLoadingScene_H_

#include "LoadingScene.h"

class EndGameLoadingScene : public LoadingScene {
    
public:
  
  static EndGameLoadingScene* node(int chapter);
  
  EndGameLoadingScene(int chapter);
  
  void setupTasks();
  
  void changeScene();
  
private:
  
  int chapter_;
  
};

#endif

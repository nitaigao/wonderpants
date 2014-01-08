#ifndef BootLoaderScene_H_
#define BootLoaderScene_H_

#include "LoadingScene.h"

class BootLoaderScene : public LoadingScene {
  
public:

  static BootLoaderScene* node();
  
public:
  
  void setupTasks();
    
  void changeScene();
    
};

#endif

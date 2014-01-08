#ifndef __TITLE_SCENE_H
#define __TITLE_SCENE_H

#include "Scene.h"

class TitleScene : public Scene<TitleScene> {

public:
    
  bool init();
  
  void play();
  
  void options();
  
};

#endif

#ifndef GameTransitionScene_H_
#define GameTransitionScene_H_

#include "TransitionScene.h"

class GameTransitionScene : public TransitionScene {
  
public:
  
  static GameTransitionScene* node(int chapter, int level);
  
private:
  
  GameTransitionScene(int chapter, int level);
  
private:
  
  void finish();
  
private:
  
  int chapter_;
  int level_;
  
};

#endif

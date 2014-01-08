#ifndef TransitionScene_H_
#define TransitionScene_H_

#include "cocos2d.h"

class TransitionScene : public cocos2d::CCScene {
  
public:

  virtual ~TransitionScene() { };
  
public:
  
  bool init();
  
  void onEnterTransitionDidFinish();
    
private:
  
  void finishUp();
  
  virtual void finish() = 0;
  
};

#endif

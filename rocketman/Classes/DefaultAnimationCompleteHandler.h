#ifndef DefaultAnimationCompleteHandler_H_
#define DefaultAnimationCompleteHandler_H_

#include "AnimationCompleteHandler.h"

class DefaultAnimationCompleteHandler : public AnimationCompleteHandler {

public:
  
  static AnimationCompleteHandler* handler();
  
public:
  
  void animationComplete();
  
public:
  
  AnimationCompleteHandler* clone();
  
private:
  
  DefaultAnimationCompleteHandler();
  
};

#endif

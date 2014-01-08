#ifndef AnimationCompleteHandler_H_
#define AnimationCompleteHandler_H_

class AnimationCompleteHandler {
  
public:
  
  virtual ~AnimationCompleteHandler() { };
  
public:
  
  virtual void animationComplete() = 0;
  
public:
  
  virtual AnimationCompleteHandler* clone() = 0;
  
};

#endif
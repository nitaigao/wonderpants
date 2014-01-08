#ifndef ScriptAnimationCompleteHandler_H_
#define ScriptAnimationCompleteHandler_H_

#include "AnimationCompleteHandler.h"

class lua_State;

class ScriptAnimationCompleteHandler : public AnimationCompleteHandler {
  
public:
  
  static ScriptAnimationCompleteHandler* handler(lua_State* state, int functionId);
  
public:
  
  void animationComplete();
  
public:
  
  AnimationCompleteHandler* clone();
  
private:
  
  ScriptAnimationCompleteHandler(lua_State* state, int functionId);
  
private:
  
  lua_State* state_;
  int functionId_;
    
};

#endif

#include "DefaultAnimationCompleteHandler.h"

AnimationCompleteHandler* DefaultAnimationCompleteHandler::handler() {
  return new DefaultAnimationCompleteHandler();
}

void DefaultAnimationCompleteHandler::animationComplete() {
  // do nothing
}

DefaultAnimationCompleteHandler::DefaultAnimationCompleteHandler() {
  
}

AnimationCompleteHandler* DefaultAnimationCompleteHandler::clone() {
  return new DefaultAnimationCompleteHandler();
}
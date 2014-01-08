#ifndef CreditsScene_H_
#define CreditsScene_H_

#include "Scene.h"

class CreditsScene : public Scene<CreditsScene> {
  
public:
  
  bool init();
  
  void back(cocos2d::CCObject* sender);
  
};

#endif

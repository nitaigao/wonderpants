#ifndef OptionsScene_H_
#define OptionsScene_H_

#include "Scene.h"

class OptionsScene : public Scene<OptionsScene> {
  
public:
  
  bool init();
    
  void resetGame(cocos2d::CCObject* sender);
  
  void flipScreen(cocos2d::CCObject* sender);
  
  void credits(cocos2d::CCObject* sender);
  
  void back(cocos2d::CCObject* sender);
  
#ifdef CHEATS
  void cheats(cocos2d::CCObject* sender);
#endif
  
};

#endif

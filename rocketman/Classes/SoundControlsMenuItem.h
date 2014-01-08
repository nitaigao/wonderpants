#ifndef SoundControlsMenuItem_H_
#define SoundControlsMenuItem_H_

#include "CCMenuItem.h"

class SoundControlsMenuItem : public cocos2d::CCMenuItem {
  
  void init();
  
  void toggleSFX(cocos2d::CCObject* sender);
  
  void toggleMusic(cocos2d::CCObject* sender);
  
  void toggleVibrate(cocos2d::CCObject* sender);
  
public:
  
 static SoundControlsMenuItem* node();
  
};

#endif

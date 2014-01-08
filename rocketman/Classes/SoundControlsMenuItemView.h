#ifndef SoundControlsMenuItemView_H_
#define SoundControlsMenuItemView_H_

#include "CCNode.h"

class SoundControlsMenuItemView : public cocos2d::CCNode {
  
  void toggle(int stag, bool state);
  
public:
  
  static SoundControlsMenuItemView* itemWithController(cocos2d::SelectorProtocol *rec, cocos2d::SEL_MenuHandler sfxSelector, cocos2d::SEL_MenuHandler musicSelector, cocos2d::SEL_MenuHandler vibrateSelector);
  
  void initWithController(cocos2d::SelectorProtocol *rec, cocos2d::SEL_MenuHandler sfxSelector, cocos2d::SEL_MenuHandler musicSelector, cocos2d::SEL_MenuHandler vibrateSelector);
  
  void setMusicState(bool state);
  
  void setVibrateState(bool state);
  
  void setSFXState(bool state);
  
};

#endif

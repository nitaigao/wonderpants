#ifndef ButtonLabelMenuItem_H_
#define ButtonLabelMenuItem_H_

#include "CCMenuItem.h"

class ButtonLabelMenuItem : public cocos2d::CCMenuItemSprite {
  
public:
  
  static ButtonLabelMenuItem* itemWithText(const char* text, cocos2d::SelectorProtocol *rec, cocos2d::SEL_MenuHandler selector);
  
  void initWithText(const char* text, cocos2d::SelectorProtocol *rec, cocos2d::SEL_MenuHandler selector);
  
  void setOpacity(int opacity);
  
private:
  
  void onPushed(cocos2d::CCObject* object);
  
private:
  
  cocos2d::SEL_MenuHandler handler;
  SelectorProtocol* controller;
  
};

#endif

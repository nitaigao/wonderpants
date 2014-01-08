#ifndef ButtonSpriteMenuItem_H_
#define ButtonSpriteMenuItem_H_

#include "cocos2d.h"
USING_NS_CC;

class ButtonSpriteMenuItem : public cocos2d::CCMenuItemSprite {
  
public:
  
  static ButtonSpriteMenuItem* itemFromNormalSprite(CCNode* normalSprite, CCNode* selectedSprite, SelectorProtocol* target, SEL_MenuHandler selector);
  
  bool initFromNormalSprite(CCNode* normalSprite, CCNode* selectedSprite, CCNode* disabledSprite, SelectorProtocol* target, SEL_MenuHandler selector);
  
private:
  
  void onPushed(cocos2d::CCObject* object);
  
private:
  
  cocos2d::SEL_MenuHandler handler;
  SelectorProtocol* controller;

  
};

#endif

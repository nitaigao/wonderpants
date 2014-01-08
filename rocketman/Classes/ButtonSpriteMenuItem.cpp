#include "ButtonSpriteMenuItem.h"

#include "SoundSystem.h"

ButtonSpriteMenuItem* ButtonSpriteMenuItem::itemFromNormalSprite(CCNode* normalSprite, CCNode* selectedSprite, SelectorProtocol* target, SEL_MenuHandler selector) {
  ButtonSpriteMenuItem* item = new ButtonSpriteMenuItem();
  item->initFromNormalSprite(normalSprite, selectedSprite, NULL, target, selector);
  item->autorelease();
  return item;
}

bool ButtonSpriteMenuItem::initFromNormalSprite(CCNode* normalSprite, CCNode* selectedSprite, CCNode* disabledSprite, SelectorProtocol* target, SEL_MenuHandler selector) {
  CCMenuItemSprite::initFromNormalSprite(normalSprite, selectedSprite, disabledSprite, this, menu_selector(ButtonSpriteMenuItem::onPushed));
  controller = target;
  handler = selector;
  
  return true;
}

void ButtonSpriteMenuItem::onPushed(cocos2d::CCObject* object) {
  SoundSystem::sharedSoundSystem()->playEffect("menu_click");
  if (controller) {
    (controller->*handler)(object);
  }
}
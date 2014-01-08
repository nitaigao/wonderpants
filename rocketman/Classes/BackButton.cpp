#include "BackButton.h"

#include "cocos2d.h"
USING_NS_CC;

#include "SoundSystem.h"

BackButton* BackButton::itemWithController(cocos2d::SelectorProtocol *controller, cocos2d::SEL_MenuHandler selector) {
  BackButton* button = new BackButton();
  button->initWithController(controller, selector);
  button->autorelease();
  return button;
}

void BackButton::initWithController(cocos2d::SelectorProtocol *rec, cocos2d::SEL_MenuHandler selector) {
  CCMenu* menu = CCMenu::node();
  CCSize screenSize = CCDirector::sharedDirector()->getCompatibleWinSize();
  CCPoint origin = CCDirector::sharedDirector()->getCompatibleOrigin();
  
  menu->setPosition(ccp(origin.x + 30, screenSize.height - origin.y - 30));
  
  {
    CCSprite* up = CCSprite::spriteWithSpriteFrameName("button_back.png");
    CCSprite* down = CCSprite::spriteWithSpriteFrameName("button_back_down.png");
    
    controller = rec;
    handler = selector;

    CCMenuItemSprite* item = CCMenuItemSprite::itemFromNormalSprite(up, down, this, menu_selector(BackButton::onPushed));
    menu->addChild(item, 0);
  }
  
  this->addChild(menu);
}

void BackButton::onPushed(cocos2d::CCObject* object) {
  SoundSystem::sharedSoundSystem()->playEffect("menu_click");
  (controller->*handler)(object);
}
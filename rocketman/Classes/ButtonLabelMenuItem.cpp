#include "ButtonLabelMenuItem.h"

#include "cocos2d.h"
USING_NS_CC;

#include "CClabelBNFont.h"
#include "SoundSystem.h"

static const int TAG_LABEL = 100;

ButtonLabelMenuItem* ButtonLabelMenuItem::itemWithText(const char* text, cocos2d::SelectorProtocol *rec, cocos2d::SEL_MenuHandler selector) {
  ButtonLabelMenuItem *pRet = new ButtonLabelMenuItem();
  pRet->initWithText(text, rec, selector);
  pRet->autorelease();
  return pRet;
}

void ButtonLabelMenuItem::initWithText(const char* text, cocos2d::SelectorProtocol *rec, cocos2d::SEL_MenuHandler selector) {
  CCSprite* up = CCSprite::spriteWithSpriteFrameName("button.png");
  CCSprite* down = CCSprite::spriteWithSpriteFrameName("button_down.png");
  
  controller = rec;
  handler = selector;
  
  initFromNormalSprite(up, down, NULL, this, menu_selector(ButtonLabelMenuItem::onPushed)); 

  CCLabelBNFont* font = CCLabelBNFont::labelWithString(text, "soupofjustice_28_white.fnt", CCTextAlignmentCenter);

  CCSize contentSize = getContentSize();
  CCSize fontContentSize = font->getContentSizeInPixels();
    
  font->setPosition(ccp(getContentSize().width / 2.0f, getContentSize().height / 2.0f));
  
  addChild(font, 0, TAG_LABEL);
}

void ButtonLabelMenuItem::onPushed(cocos2d::CCObject* object) {
  SoundSystem::sharedSoundSystem()->playEffect("menu_click");
  (controller->*handler)(object);
}

void ButtonLabelMenuItem::setOpacity(int opacity) {
  CCMenuItemSprite::setOpacity(opacity);
  static_cast<CCLabelBNFont*>(getChildByTag(TAG_LABEL))->setOpacity(opacity);
}
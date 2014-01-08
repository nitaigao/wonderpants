#include "SoundControlsMenuItemView.h"

#include "cocos2d.h"
USING_NS_CC;

static const int TAG_MENU = 100;
static const int TAG_MUSIC = 101;
static const int TAG_SFX = 102;
static const int TAG_VIBRATE = 103;

SoundControlsMenuItemView* SoundControlsMenuItemView::itemWithController(cocos2d::SelectorProtocol *rec, cocos2d::SEL_MenuHandler sfxSelector, cocos2d::SEL_MenuHandler musicSelector, cocos2d::SEL_MenuHandler vibrateSelector) {
  SoundControlsMenuItemView* item = new SoundControlsMenuItemView();
  item->initWithController(rec, sfxSelector, musicSelector, vibrateSelector);
  item->autorelease();
  return item;
}

CCMenuItemSprite* createButton(const char* upAsset, const char* downAsset) {
  CCSprite* up = CCSprite::spriteWithSpriteFrameName(upAsset);
  CCSprite* down = CCSprite::spriteWithSpriteFrameName(downAsset);
  return CCMenuItemSprite::itemFromNormalSprite(up, down);
}

void SoundControlsMenuItemView::initWithController(cocos2d::SelectorProtocol *rec, cocos2d::SEL_MenuHandler sfxSelector, cocos2d::SEL_MenuHandler musicSelector, cocos2d::SEL_MenuHandler vibrateSelector) {
  CCMenu* menu = CCMenu::node();
  menu->setPosition(ccp(0, 0));
  
  {
    CCMenuItemSprite* on = createButton("button_speakers_on.png", "button_speakers_on_down.png");    
    CCMenuItemSprite* off = createButton("button_speakers_off.png", "button_speakers_off_down.png");    
    CCMenuItemToggle* toggle = CCMenuItemToggle::itemWithItem(on);
    toggle->addSubItem(off);
    toggle->setTarget(rec, sfxSelector);
    menu->addChild(toggle, 0, TAG_SFX);
  }
  
  {
    CCMenuItemSprite* on = createButton("button_music_on.png", "button_music_on_down.png");    
    CCMenuItemSprite* off = createButton("button_music_off.png", "button_music_off_down.png");    
    CCMenuItemToggle* toggle = CCMenuItemToggle::itemWithItem(on);
    toggle->addSubItem(off);
    toggle->setTarget(rec, musicSelector);
    menu->addChild(toggle, 0, TAG_MUSIC);
  }
  
  {
    CCMenuItemSprite* on = createButton("button_vibrate_on.png", "button_vibrate_on_down.png");    
    CCMenuItemSprite* off = createButton("button_vibrate_off.png", "button_vibrate_off_down.png");    
    CCMenuItemToggle* toggle = CCMenuItemToggle::itemWithItem(on);
    toggle->addSubItem(off);
    toggle->setTarget(rec, vibrateSelector);
    menu->addChild(toggle, 0, TAG_VIBRATE);    
  }
  
  menu->alignItemsHorizontallyWithPadding(30);
  this->addChild(menu, 0, TAG_MENU);
  
  {
    float width = menu->getContentSize().width;
    float height = ((CCNode*)menu->getChildren()->lastObject())->getContentSize().height;
    setContentSize(CCSize(width, height));  
  }  
}

void SoundControlsMenuItemView::toggle(int tag, bool state) {
  CCMenu* menu = (CCMenu*)getChildByTag(TAG_MENU);
  CCMenuItemToggle* toggle = (CCMenuItemToggle*)menu->getChildByTag(tag);
  toggle->setSelectedIndex(!state);
}

void SoundControlsMenuItemView::setMusicState(bool state) {
  toggle(TAG_MUSIC, state);
}

void SoundControlsMenuItemView::setVibrateState(bool state) {
  toggle(TAG_VIBRATE, state);
}

void SoundControlsMenuItemView::setSFXState(bool state) {
  toggle(TAG_SFX, state);
}

#include "SoundControlsMenuItem.h"

#include "cocos2d.h"
USING_NS_CC;

#include "SoundControlsMenuItemView.h"
#include "SoundSystem.h"

SoundControlsMenuItem* SoundControlsMenuItem::node() {
  SoundControlsMenuItem* item = new SoundControlsMenuItem();
  item->init();
  item->autorelease();
  return item;
}

void SoundControlsMenuItem::init() {
  SoundControlsMenuItemView* view = SoundControlsMenuItemView::itemWithController(this, 
                                                menu_selector(SoundControlsMenuItem::toggleSFX), 
                                                menu_selector(SoundControlsMenuItem::toggleMusic),
                                                menu_selector(SoundControlsMenuItem::toggleVibrate));
  
  bool musicState = SoundSystem::sharedSoundSystem()->musicState();
  view->setMusicState(musicState);
  
  bool sfxState = SoundSystem::sharedSoundSystem()->sfxState();
  view->setSFXState(sfxState);

  bool vibrateState = SoundSystem::sharedSoundSystem()->vibrateState();
  view->setVibrateState(vibrateState);
  
  addChild(view);
  setContentSize(view->getContentSize());
}

void SoundControlsMenuItem::toggleSFX(CCObject* sender) {
  SoundSystem::sharedSoundSystem()->playEffect("menu_click");
  SoundSystem::sharedSoundSystem()->toggleSFX();
}

void SoundControlsMenuItem::toggleMusic(cocos2d::CCObject* sender) {
  SoundSystem::sharedSoundSystem()->playEffect("menu_click");
  SoundSystem::sharedSoundSystem()->toggleMusic();
}

void SoundControlsMenuItem::toggleVibrate(cocos2d::CCObject* sender) {
  SoundSystem::sharedSoundSystem()->playEffect("menu_click");
  SoundSystem::sharedSoundSystem()->toggleVibrate();
}

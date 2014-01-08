#include "MenuCache.h"

#include "cocos2d.h"
USING_NS_CC;

#include "SimpleAudioEngine.h"
using namespace CocosDenshion;

void MenuCache::cache() {
  CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("country_backgrounds.plist");
  
  CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("city_backgrounds.plist");
  CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("jungle_backgrounds.plist");
  
  CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("fonts.plist");
  CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("ui_backgrounds.plist");
  CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("transition.plist");
  CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("chapters.plist");
  CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("chapter_comics.plist");
  
  CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("game_assets.plist");
  CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("game.plist");
  
  SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic("kh_music_title_loop_01.mp3");
  
  SimpleAudioEngine::sharedEngine()->preloadEffect("kh_music_ident_04.mp3");
  SimpleAudioEngine::sharedEngine()->preloadEffect("kh_sfx_menu_sweep_01.mp3");
  SimpleAudioEngine::sharedEngine()->preloadEffect("kh_sfx_menu_sweep_02.mp3");
  SimpleAudioEngine::sharedEngine()->preloadEffect("kh_sfx_menu_sweep_03.mp3");
  SimpleAudioEngine::sharedEngine()->preloadEffect("kh_sfx_menu_sweep_04.mp3");
  SimpleAudioEngine::sharedEngine()->preloadEffect("kh_sfx_menu_sweep_05.mp3");
  SimpleAudioEngine::sharedEngine()->preloadEffect("kh_sfx_menu_sweep_06.mp3");
  SimpleAudioEngine::sharedEngine()->preloadEffect("kh_sfx_menu_sweep_07.mp3");
  SimpleAudioEngine::sharedEngine()->preloadEffect("kh_sfx_menu_sweep_08.mp3");
}
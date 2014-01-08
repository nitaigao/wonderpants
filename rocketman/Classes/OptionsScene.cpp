#include "OptionsScene.h"

#include "cocos2d.h"
USING_NS_CC;

#include "OptionsSceneView.h"
#include "ScreenManager.h"
#include "SaveGame.h"

bool OptionsScene::init() {
  OptionsSceneView* view = OptionsSceneView::nodeWithController(this);
  this->addChild(view);
  return true;
}

void OptionsScene::resetGame(cocos2d::CCObject* sender) {
  SaveGame::sharedSaveData()->purge();
  CCUserDefault::deleteXMLFile();
}

void OptionsScene::flipScreen(cocos2d::CCObject* sender) {
  ccDeviceOrientation orientation = CCDirector::sharedDirector()->getDeviceOrientation();  
  const char* key = "SCREEN_ORIENTATION";
  
  if (orientation == kCCDeviceOrientationLandscapeLeft) {
    CCUserDefault::sharedUserDefault()->setIntegerForKey(key, kCCDeviceOrientationLandscapeRight);
    CCDirector::sharedDirector()->setDeviceOrientation(kCCDeviceOrientationLandscapeRight);
  }
  
  if (orientation == kCCDeviceOrientationLandscapeRight) {
    CCUserDefault::sharedUserDefault()->setIntegerForKey(key, kCCDeviceOrientationLandscapeLeft);
    CCDirector::sharedDirector()->setDeviceOrientation(kCCDeviceOrientationLandscapeLeft);
  }
}

void OptionsScene::credits(cocos2d::CCObject* sender) {
  ScreenManager::activateCreditsScreen();
}

void OptionsScene::back(cocos2d::CCObject* sender) {
  ScreenManager::activateTitleScreen();
}

#ifdef CHEATS
void OptionsScene::cheats(cocos2d::CCObject* sender) {
  ScreenManager::activateCheatsScreen();
}
#endif 
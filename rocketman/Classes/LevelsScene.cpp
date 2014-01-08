#include "LevelsScene.h"

#include "cocos2d.h"
USING_NS_CC;

#include "LevelSceneView.h"
#include "ScreenManager.h"
#include "ChapterData.h"
#include "SoundSystem.h"

LevelsScene* LevelsScene::nodeWithChapter(int chapter) {
  LevelsScene* scene = new LevelsScene();
  scene->initWithChapter(chapter);
  scene->autorelease();
  return scene;
}

void LevelsScene::initWithChapter(int chapter) {
  chapter_ = chapter;
  ChapterData data = ChapterData::forChapter(chapter);
  LevelSceneView* view = LevelSceneView::nodeWithController(this, data);
  this->addChild(view);
}

bool LevelsScene::init() {
  return true;
}

void LevelsScene::back(CCObject* sender) {
  ScreenManager::activateChaptersScreen(chapter_); 
}

void LevelsScene::playLevel(CCObject* sender) {
  SoundSystem::sharedSoundSystem()->playEffect("menu_click");
  CCMenuItem* item = (CCMenuItem*)sender;
  int level = item->getTag();
  ScreenManager::loadAndDisplayGameScreen(chapter_, level);
}
#include "LevelsLoadingScene.h"

#include "ScreenManager.h"
#include "SoundSystem.h"

#include "TitleLoadList.h"

LevelsLoadingScene* LevelsLoadingScene::nodeWithChapter(int chapter) {
  LevelsLoadingScene* scene = new LevelsLoadingScene();
  scene->autorelease();
  scene->initWithChapter(chapter);
  return scene;
}

void LevelsLoadingScene::initWithChapter(int chapter) {
  LoadingScene::init();
  chapter_ = chapter;
}

void LevelsLoadingScene::setupTasks() {
  TitleLoadList::fillLoadList(loadTasks_);
}

void LevelsLoadingScene::changeScene() {
  SoundSystem::sharedSoundSystem()->playMusic("title");
  ScreenManager::activateLevelsScreen(chapter_);
}
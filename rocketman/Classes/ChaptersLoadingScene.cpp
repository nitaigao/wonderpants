#include "ChaptersLoadingScene.h"

#include "ScreenManager.h"
#include "SoundSystem.h"

#include "TitleLoadList.h"

ChaptersLoadingScene* ChaptersLoadingScene::nodeWithChapter(int chapter) {
  ChaptersLoadingScene* scene = new ChaptersLoadingScene();
  scene->autorelease();
  scene->initWithChapter(chapter);
  return scene;
}

void ChaptersLoadingScene::initWithChapter(int chapter) {
  LoadingScene::init();
  chapter_ = chapter;
}

void ChaptersLoadingScene::setupTasks() {
  TitleLoadList::fillLoadList(loadTasks_);
}

void ChaptersLoadingScene::changeScene() {
  SoundSystem::sharedSoundSystem()->playMusic("title");
  ScreenManager::activateChaptersScreen(chapter_);
}
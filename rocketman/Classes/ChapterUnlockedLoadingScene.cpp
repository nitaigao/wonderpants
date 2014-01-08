#include "ChapterUnlockedLoadingScene.h"

#include "ScreenManager.h"
#include "SoundSystem.h"

#include "TitleLoadList.h"

ChapterUnlockedLoadingScene* ChapterUnlockedLoadingScene::nodeWithChapter(int chapter) {
  ChapterUnlockedLoadingScene* scene = new ChapterUnlockedLoadingScene();
  scene->autorelease();
  scene->initWithChapter(chapter);
  return scene;
}

void ChapterUnlockedLoadingScene::initWithChapter(int chapter) {
  LoadingScene::init();
  chapter_ = chapter;
}

void ChapterUnlockedLoadingScene::setupTasks() {
  TitleLoadList::fillLoadList(loadTasks_);
}

void ChapterUnlockedLoadingScene::changeScene() {
  SoundSystem::sharedSoundSystem()->playMusic("title");
  ScreenManager::activateChaptersScreenUnlockChapter(chapter_);
}
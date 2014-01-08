#include "EndGameLoadingScene.h"

#include "ScreenManager.h"
#include "SoundSystem.h"

#include "TitleLoadList.h"

EndGameLoadingScene::EndGameLoadingScene(int chapter) : chapter_(chapter) {
  
}

EndGameLoadingScene* EndGameLoadingScene::node(int chapter) {
  EndGameLoadingScene* scene = new EndGameLoadingScene(chapter);
  scene->autorelease();
  scene->init();
  return scene;
}

void EndGameLoadingScene::setupTasks() {
  TitleLoadList::fillLoadList(loadTasks_);
}

void EndGameLoadingScene::changeScene() {
  SoundSystem::sharedSoundSystem()->playMusic("title");
  ScreenManager::activateEndGameScreen(chapter_);
}
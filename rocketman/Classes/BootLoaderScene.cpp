#include "BootLoaderScene.h"

#include "ScreenManager.h"
#include "TitleLoadList.h"

BootLoaderScene* BootLoaderScene::node() {
  BootLoaderScene* scene = new BootLoaderScene();
  scene->init();
  scene->autorelease();
  return scene;
}

void BootLoaderScene::setupTasks() {  
  TitleLoadList::fillLoadList(loadTasks_);
}

void BootLoaderScene::changeScene() {
  ScreenManager::activateTitleScreen();
}

#include "TitleScene.h"

#include "TitleSceneView.h"
#include "ScreenManager.h"
#include "SoundSystem.h"

bool TitleScene::init() {
  CCNode* view = TitleSceneView::nodeWithController(this);
  this->addChild(view);
  SoundSystem::sharedSoundSystem()->playMusic(kTitleMusic);
  return true;
}

void TitleScene::play() {
  ScreenManager::activateChaptersScreen(0);
}

void TitleScene::options() {
  ScreenManager::activateOptionsScreen();
}

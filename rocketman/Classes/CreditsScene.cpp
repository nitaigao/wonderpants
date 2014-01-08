#include "CreditsScene.h"

#include "CreditsSceneView.h"
#include "ScreenManager.h"

bool CreditsScene::init() {
  CreditsSceneView* view = CreditsSceneView::nodeWithController(this);
  this->addChild(view);
  return true;
}

void CreditsScene::back(cocos2d::CCObject* sender) {
  ScreenManager::activateOptionsScreen();
}
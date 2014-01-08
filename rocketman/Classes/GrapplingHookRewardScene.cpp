#include "GrapplingHookRewardScene.h"

#include "GrapplingHookRewardSceneView.h"

#include "ScreenManager.h"

GrapplingHookRewardScene* GrapplingHookRewardScene::nodeWithChapter(int chapter, int level) {
  GrapplingHookRewardScene* scene = new GrapplingHookRewardScene(chapter, level);
  scene->init();
  scene->autorelease();
  return scene;
}

GrapplingHookRewardScene::GrapplingHookRewardScene(int chapter, int level) : chapter_(chapter), level_(level) {
  
}

bool GrapplingHookRewardScene::init() {
  GrapplingHookRewardSceneView* view = GrapplingHookRewardSceneView::nodeWithController(this);
  addChild(view);
  return true;
}

void GrapplingHookRewardScene::continueToGame() {
  ScreenManager::activateGameScreen(chapter_, level_);
}
#include "ParachuteRewardScene.h"

#include "ParachuteRewardSceneView.h"

#include "ScreenManager.h"

ParachuteRewardScene* ParachuteRewardScene::nodeWithChapter(int chapter, int level) {
  ParachuteRewardScene* scene = new ParachuteRewardScene(chapter, level);
  scene->init();
  scene->autorelease();
  return scene;
}

ParachuteRewardScene::ParachuteRewardScene(int chapter, int level) : chapter_(chapter), level_(level) {
  
}

bool ParachuteRewardScene::init() {
  ParachuteRewardSceneView* view = ParachuteRewardSceneView::nodeWithController(this);
  addChild(view);
  return true;
}

void ParachuteRewardScene::continueToGame() {
  ScreenManager::activateGameScreen(chapter_, level_);
}
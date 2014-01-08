#include "GameTransitionScene.h"

#include "ScreenManager.h"

GameTransitionScene::GameTransitionScene(int chapter, int level) : chapter_(chapter), level_(level) {
  
}

GameTransitionScene* GameTransitionScene::node(int chapter, int level) {
  GameTransitionScene* node = new GameTransitionScene(chapter, level);
  node->init();
  node->autorelease();
  return node;
}

void GameTransitionScene::finish() {
  ScreenManager::cutToGameScreen(chapter_, level_);
}


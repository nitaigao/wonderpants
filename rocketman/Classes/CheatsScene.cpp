#include "CheatsScene.h"

#include "CheatsSceneView.h"
#include "SaveGame.h"
#include "ChapterData.h"
#include "ScreenManager.h"
#include "SaveState.h"

CheatsScene* CheatsScene::node() {
  CheatsScene* node = new CheatsScene();
  node->init();
  node->autorelease();
  return node;
}

bool CheatsScene::init() {
  CheatsSceneView* view = CheatsSceneView::nodeWithController(this);
  addChild(view);
  
  return true;
}

void unlockChapter(int chapter) {
  int levelCount = ChapterData::chapters().first().levels();
  for (int i = 0; i < levelCount; i++) {
    SaveState saveState(chapter, i, 3, 7000, 1, 1000);
    SaveGame::sharedSaveData()->saveProgress(saveState);
  }  
  SaveGame::sharedSaveData()->commit();
}

void CheatsScene::unlockChapter1() {
  unlockChapter(0);
}

void CheatsScene::unlockChapter2() {
  unlockChapter(1);
}

void CheatsScene::unlockChapter3() {
  unlockChapter(2);
}

void CheatsScene::back() {
  ScreenManager::activateOptionsScreen();
}
#include "EndGameScene.h"

#include "EndGameSceneView.h"
#include "ScreenManager.h"

#include "cocos2d.h"
USING_NS_CC;

EndGameScene::EndGameScene(int chapter) : chapter_(chapter) {
  
}

EndGameScene* EndGameScene::node(int chapter) {
  EndGameScene* node = new EndGameScene(chapter);
  node->init();
  node->autorelease();
  return node;
}

bool EndGameScene::init() {
  
  {
    EndGameSceneView* view = EndGameSceneView::nodeWithController(this);
    addChild(view);
  }
  
  {
    CCSequence* sequence = CCSequence::actionOneTwo
    (
     CCDelayTime::actionWithDuration(5),
     CCCallFunc::actionWithTarget(this, callfunc_selector(EndGameScene::showThanks))
    );
    this->runAction(sequence);
  }
  
  return true;
}

void EndGameScene::showThanks() {
  ScreenManager::activateChaptersScreenUnlockChapter(chapter_ + 1);
}
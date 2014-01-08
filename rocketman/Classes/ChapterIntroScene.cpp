#include "ChapterIntroScene.h"

#include "ChapterIntroSceneView.h"
#include "ScreenManager.h"

#include "cocos2d.h"
USING_NS_CC;

ChapterIntroScene* ChapterIntroScene::nodeWithChapter(int chapter) {
  ChapterIntroScene* scene = new ChapterIntroScene(chapter);
  scene->init();
  scene->autorelease();
  return scene;
}

ChapterIntroScene::ChapterIntroScene(int chapter) : chapter_(chapter) {

}

void ChapterIntroScene::init() {
  ChapterIntroSceneView* view = ChapterIntroSceneView::nodeWithController(this, chapter_);
  addChild(view);
  
  CCTouchDispatcher::sharedDispatcher()->addTargetedDelegate(this, 0, true);
}


void ChapterIntroScene::continueToGame() {
  CCTouchDispatcher::sharedDispatcher()->removeDelegate(this);
  ScreenManager::loadAndDisplayGameScreen(chapter_, 0);
}

bool ChapterIntroScene::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent) {
  continueToGame();
  return true;
}
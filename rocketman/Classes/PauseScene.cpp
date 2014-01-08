#include "PauseScene.h"

#include "PauseSceneView.h"
#include "ScreenManager.h"
#include "GameScene.h"

PauseScene* PauseScene::sceneWithChapter(int chapter, GameScene* controller) {
  PauseScene* scene = new PauseScene();
  scene->initWithChapter(chapter, controller);
  scene->autorelease();
  return scene;
}

void PauseScene::initWithChapter(int chapter, GameScene* controller) {
  PauseSceneView* view = PauseSceneView::nodeWithController(this);
  this->addChild(view);
  
  chapter_ = chapter;
  controller_ = controller;
}

bool PauseScene::init() {  
  return true;
}

void PauseScene::levelSelect(cocos2d::CCObject* sender) {
  ScreenManager::loadAndLevelsScreen(chapter_);
}

void PauseScene::chapterSelect(cocos2d::CCObject* sender) {
  ScreenManager::loadAndChaptersScreen(chapter_);
}

void PauseScene::resumeGame(cocos2d::CCObject* sender) {
  controller_->resumeGame(sender);
}
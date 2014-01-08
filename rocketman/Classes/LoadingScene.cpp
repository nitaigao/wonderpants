#include "LoadingScene.h"
#include "LoadingProgressBar.h"

#include "CacheMaster.h"

#include "cocos2d.h"
USING_NS_CC;

static const int TAG_PROGRESS = 101;

static const int CACHE_CLEAR_WAIT_FRAMES = 50;

LoadingScene::LoadingScene() : fullTaskCount_(0), frame_(0) {
  
}

bool LoadingScene::init() {  
  CCSize screenSize = CCDirector::sharedDirector()->getWinSize();
  
  CCSprite* bg = CCSprite::spriteWithFile("loading_screen_general.jpg");
  bg->setPosition(ccp(screenSize.width / 2, screenSize.height / 2));
  this->addChild(bg);
    
  LoadingProgressBar* progress = LoadingProgressBar::node();
  progress->setPosition(ccp(screenSize.width - 131, 60));
  addChild(progress, progress->getZOrder(), TAG_PROGRESS);
  
  setupTasks();
  fullTaskCount_ = loadTasks_.size();
  
  return true;
}

void LoadingScene::setProgress(float progress) {
  static_cast<LoadingProgressBar*>(getChildByTag(TAG_PROGRESS))
    ->setProgress(progress);
}

void LoadingScene::update(cocos2d::ccTime dt) {
  // TODO: A bug in cocos2d causes some newly loaded pvr.ccz textures to be dropped after the cache clear
  if (frame_++ < CACHE_CLEAR_WAIT_FRAMES) return;
  
  if (loadTasks_.size()) {
    ILoadTask* task = loadTasks_.front();
    task->execute();
    loadTasks_.pop();
    delete task;
  }
  
  float progress = (fullTaskCount_ - loadTasks_.size()) / (float)fullTaskCount_;
  setProgress(progress);
  
  if (!loadTasks_.size()) {
    this->unscheduleUpdate();
    this->changeScene();
  }
}

void LoadingScene::onEnterTransitionDidFinish() { 
  CacheMaster::purgeAllCaches();
  CCScene::onEnter();
  this->scheduleUpdate();  
}
#include "GameScene.h"

#include "Common.h"

#include "cocos2d.h"
USING_NS_CC;

#include "Value.h"

#include "GameUI.h"
#include "PauseScene.h"
#include "GameView.h"
#include "LevelEndView.h"
#include "PhysicsDebugView.h"

#include "Input.h"
#include "Platform.h"

#include "Level.h"
#include "EventSystem.h"
#include "Physics.h"
#include "PlayerState.h"

#include "ContactListener.h"
#include "LevelCache.h"

#include "SaveGame.h"
#include "GameState.h"

#include "SaveState.h"

#include "EntitySystem.h"
#include "SoundSystem.h"
#include "ScriptManager.h"

#include "ChapterData.h"
#include "GameConfig.h"

#include "ScreenManager.h"
#include "EndOfLevelStrategy.h"
#include "StatsTracker.h"

static const int TAG_PAUSE = 100;
static const int TAG_VIEW = 102;
static const int TAG_UI = 103;
static const int TAG_INPUT = 104;

static const int Z_PHYSICS_DEBUG = 900;
static const int Z_PAUSE = 999;

static const float DELAY_WIN = 1.5f;

GameScene* GameScene::nodeWithChapter(int chapter, int level, int attempts) {
  GameScene* scene = new GameScene();
  scene->initWithChapter(chapter, level, attempts);
  scene->autorelease();
  return scene;
}

GameScene::GameScene()
  : level_(nullptr)
  , eventSystem_(new EventSystem)
  , physics_(new Physics)
  , playerState_(new PlayerState) 
{ }

GameScene::~GameScene() {
  {
    eventSystem_->unsubscribeEvent("targetable_collected", this, &GameScene::targetableCollected);
    eventSystem_->unsubscribeEvent("launchable_crashed", this, &GameScene::launchableCrashed);
    eventSystem_->unsubscribeEvent("air_fail", this, &GameScene::launchableCrashed);
  }
  
  {
    this->unscheduleUpdate();
  }
  
  {
    SAFE_DELETE(level_);
    SAFE_DELETE(physics_);
    SAFE_DELETE(eventSystem_);
    SAFE_DELETE(playerState_);
  }
}

void GameScene::setupLevel(Level* level) {
  GameView* view = (GameView*)getChildByTag(TAG_VIEW);
  GameUI* ui = (GameUI*)getChildByTag(TAG_UI);
  level->setup(attempts_, view, ui, physics_, eventSystem_, playerState_);
  eventSystem_->postEvent("state_changed", STATE_LEVEL_START);  
}

void GameScene::initWithChapter(int chapter, int level, int attempts) { 
  {
    chapterIndex_ = chapter;
    levelIndex_ = level;
    attempts_ = attempts;
    levelTimer_.start();
    isPaused_ = false;
  }

  {
    CCAnimationCache::purgeSharedAnimationCache();
  }
    
  {
    GameView* view = GameView::node();
    this->addChild(view, view->getZOrder(), TAG_VIEW);
    
    PhysicsDebugView* debugView = PhysicsDebugView::node(physics_);
    view->addChild(debugView, Z_PHYSICS_DEBUG);
  }
  
  {
    Input* input = Input::node(eventSystem_);
    addChild(input, input->getZOrder(), TAG_INPUT);
  }
  
  {
    GameUI* ui = GameUI::nodeWithController(this, chapter, level);
    addChild(ui, ui->getZOrder(), TAG_UI);
  }
  
  {
    level_ = LevelCache::sharedCache()->level(level);    
    setupLevel(level_);
  }
    
  {
    ContactListener* contactListener = new ContactListener(physics_, level_, eventSystem_);
    physics_->setContactListener(contactListener);
  }
  
  {
    SoundSystem::sharedSoundSystem()->playMusic("game");
  }
  
  {
    this->scheduleUpdate();
  }
  
  {
    eventSystem_->subscribeEvent("targetable_collected", this, &GameScene::targetableCollected);
    eventSystem_->subscribeEvent("launchable_crashed", this, &GameScene::launchableCrashed);
    eventSystem_->subscribeEvent("air_fail", this, &GameScene::launchableCrashed);
  }
}

void GameScene::targetableCollected(const String& event, const Array<Value>& data) {
  eventSystem_->postEvent("state_changed", STATE_LEVEL_WIN);
  levelTimer_.stop();
  this->schedule(schedule_selector(GameScene::winLevel), DELAY_WIN);
  
  SaveState saveState(chapterIndex_, levelIndex_, playerState_->coins(), playerState_->bonus(), attempts_, levelTimer_.split());
  
  int oldScore = SaveGame::sharedSaveData()->getScore(levelIndex_, chapterIndex_);
  StatsTracker().winLevel(saveState);
  
  if (saveState.score() > oldScore) {
    SaveGame::sharedSaveData()->saveProgress(saveState);
    SaveGame::sharedSaveData()->commit();
  }
}

void GameScene::launchableCrashed(const String& event, const Array<Value>& data) {
  StatsTracker().loseLevel(levelIndex_, chapterIndex_);
  eventSystem_->postEvent("state_changed", STATE_LEVEL_LOST);
  schedule(schedule_selector(GameScene::restartGame), 2.7f);
}

void GameScene::draw() {
  physics_->drawDebug();
  CCScene::draw();
}

void GameScene::update(float dt) {
  eventSystem_->update();
  if (!isPaused_) {
    level_->update(dt);
    physics_->update(dt);
  }
}

void GameScene::pauseGame(cocos2d::CCObject* sender) {
  static_cast<GameView*>(getChildByTag(TAG_VIEW))->onExit();
  PauseScene* pause = PauseScene::sceneWithChapter(chapterIndex_, this);
  this->addChild(pause, Z_PAUSE, TAG_PAUSE);
  isPaused_ = true;
  static_cast<Input*>(getChildByTag(TAG_INPUT))->pause();
}

void GameScene::restartGame(cocos2d::CCObject* sender) {
  this->unscheduleUpdate();
  getChildByTag(TAG_VIEW)->onExit();
  
  unschedule(schedule_selector(GameScene::restartGame));
  GameScene* scene = GameScene::nodeWithChapter(chapterIndex_, levelIndex_, attempts_ + 1);
  CCTransitionFade* fade = CCTransitionFade::transitionWithDuration(0.2f, scene, ccWHITE);
  CCDirector::sharedDirector()->replaceScene(fade);
}

void GameScene::winLevel() {
  this->unschedule(schedule_selector(GameScene::winLevel));
  this->removeChildByTag(TAG_UI, true);
 
  String background = ChapterData::forChapter(chapterIndex_).background();
  GameView* view = (GameView*)getChildByTag(TAG_VIEW);
  view->fadeScene(background);
  
  int collectableScore = playerState_->coins() * 1000;
  int styleScore = playerState_->bonus();
  int timeScore = !time ? 0 : 2000.0f / levelTimer_.split();
  int score = collectableScore + timeScore + styleScore;
  
  LevelEndView* levelEnd = LevelEndView::node(this, 
                                              chapterIndex_, 
                                              levelIndex_, 
                                              playerState_->coins(), 
                                              levelTimer_.split(),
                                              score);
  addChild(levelEnd);
}

void GameScene::resumeGame(cocos2d::CCObject* sender) {
  this->removeChildByTag(TAG_PAUSE, true);
  static_cast<GameView*>(getChildByTag(TAG_VIEW))->onEnter();
  isPaused_ = false;
  static_cast<Input*>(getChildByTag(TAG_INPUT))->resume();
}

void GameScene::nextLevel(cocos2d::CCObject *sender) {
  EndOfLevelStrategy::strategy(chapterIndex_, levelIndex_ + 1)->execute();
}

void GameScene::levelSelect(cocos2d::CCObject *sender) {
  ScreenManager::loadAndLevelsScreen(chapterIndex_);
}
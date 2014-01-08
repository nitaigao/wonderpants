#include "LevelEndView.h"

#include "Common.h"
#include "CClabelBNFont.h"
#include "GameScene.h"
#include "SoundSystem.h"
#include "TimeCountUpAction.h"
#include "ScoreCountUpAction.h"
#include "ButtonSpriteMenuItem.h"

USING_NS_CC;

static const int TAG_FILM_TOP = 100;
static const int TAG_FILM_BOTTOM = 101;

LevelEndView::LevelEndView(GameScene* controller, int chapter, int level, int coins, int time, int score) 
  : controller_(controller)
  , chapter_(chapter)
  , level_(level)
  , coins_(coins)
  , coinAwardIndex_(0)
  , time_(time)
  , score_(score) { }

LevelEndView* LevelEndView::node(GameScene* controller, int chapter, int level, int coins, int time, int score) {
  LevelEndView* node = new LevelEndView(controller, chapter, level, coins, time, score);
  node->autorelease();
  return node;
}

void LevelEndView::onEnter() {
  CCNode::onEnter();
  
  {
    int height = 100;
    {
      CCSize screenSize = CCDirector::sharedDirector()->getWinSize();
      CCSprite* topFilm = CCSprite::sprite();
      topFilm->setColor(ccBLACK);
      topFilm->setTextureRect(CCRectMake(0, 0, screenSize.width, height));
      topFilm->setTag(TAG_FILM_TOP);
      topFilm->setPosition(ccp(screenSize.width/2, screenSize.height + height));
      addChild(topFilm);
      
      CCMoveBy* move = CCMoveBy::actionWithDuration(1.0f, ccp(0, -height));
      CCEaseBackOut* moveEase = CCEaseBackOut::actionWithAction(move);
      topFilm->runAction(moveEase);
    }
    
    {
      CCSize screenSize = CCDirector::sharedDirector()->getWinSize();
      CCSprite* bottomFilm = CCSprite::sprite();
      bottomFilm->setColor(ccBLACK);
      bottomFilm->setTextureRect(CCRectMake(0, 0, screenSize.width, height));
      bottomFilm->setTag(TAG_FILM_TOP);
      bottomFilm->setPosition(ccp(screenSize.width/2, 0 - height));
      addChild(bottomFilm);
      
      CCMoveBy* move = CCMoveBy::actionWithDuration(1.0f, ccp(0, height));
      CCEaseBackOut* moveEase = CCEaseBackOut::actionWithAction(move);
      
      CCCallFunc* showButtons = CCCallFunc::actionWithTarget(this, callfunc_selector(LevelEndView::showButtons));
      CCSequence* sequence = CCSequence::actionOneTwo(moveEase, showButtons);
      bottomFilm->runAction(sequence);      
    }
  }
}

void LevelEndView::showButtons() {
  CCSize screenSize = CCDirector::sharedDirector()->getWinSize();
  
  CCSprite* up = CCSprite::spriteWithSpriteFrameName("button_play.png");
  CCSprite* down = CCSprite::spriteWithSpriteFrameName("button_play_down.png");
  ButtonSpriteMenuItem* button = ButtonSpriteMenuItem::itemFromNormalSprite(up, down, controller_, 
                                                                            menu_selector(GameScene::nextLevel));
  CCMenu* menu = CCMenu::menuWithItem(button);
  menu->setPosition(ccp(screenSize.width/2, -40));
  addChild(menu);
  
  CCMoveBy* menuMoveUp = CCMoveBy::actionWithDuration(0.15, ccp(0, 80));
  CCEaseBackOut* menuEase = CCEaseBackOut::actionWithAction(menuMoveUp);
  
  CCCallFunc* showNext = CCCallFunc::actionWithTarget(this, callfunc_selector(LevelEndView::showLevelsButton));
  CCCallFunc* showLevel = CCCallFunc::actionWithTarget(this, callfunc_selector(LevelEndView::showLevel));
  CCFiniteTimeAction* sequence = CCSequence::actions(menuEase, showNext, showLevel, NULL);
  menu->runAction(sequence);
}

void LevelEndView::showLevelsButton() {
  CCSize screenSize = CCDirector::sharedDirector()->getWinSize();
  CCSprite* up = CCSprite::spriteWithSpriteFrameName("button_back.png");
  CCSprite* down = CCSprite::spriteWithSpriteFrameName("button_back_down.png");
  ButtonSpriteMenuItem* button = ButtonSpriteMenuItem::itemFromNormalSprite(up, down, controller_, 
                                                                            menu_selector(GameScene::levelSelect));
  CCMenu* menu = CCMenu::menuWithItem(button);
  menu->setPosition(ccp(170, -40));
  addChild(menu);
  
  CCMoveBy* menuMoveUp = CCMoveBy::actionWithDuration(0.15, ccp(0, 80));
  CCEaseBackOut* menuEase = CCEaseBackOut::actionWithAction(menuMoveUp);
  
  CCCallFunc* showNext = CCCallFunc::actionWithTarget(this, callfunc_selector(LevelEndView::showResetButton));
  CCSequence* sequence = CCSequence::actionOneTwo(menuEase, showNext);
  menu->runAction(sequence);
}

void LevelEndView::showResetButton() {
  CCSize screenSize = CCDirector::sharedDirector()->getWinSize();
  CCSprite* up = CCSprite::spriteWithSpriteFrameName("button_reset.png");
  CCSprite* down = CCSprite::spriteWithSpriteFrameName("button_reset_down.png");
  ButtonSpriteMenuItem* button = ButtonSpriteMenuItem::itemFromNormalSprite(up, down, controller_, 
                                                                            menu_selector(GameScene::restartGame));
  CCMenu* menu = CCMenu::menuWithItem(button);
  menu->setPosition(ccp(310, -40));
  addChild(menu);
  
  CCMoveBy* menuMoveUp = CCMoveBy::actionWithDuration(0.15, ccp(0, 80));
  CCEaseBackOut* menuEase = CCEaseBackOut::actionWithAction(menuMoveUp);
  
  menu->runAction(menuEase);  
}

void LevelEndView::showLevel() {
  CCSize screenSize = CCDirector::sharedDirector()->getWinSize();
  
  String levelText = String::withFormat("Level %d-%d", chapter_ + 1, level_ + 1);
  
  CCLabelBNFont* levelLabel = CCLabelBNFont::labelWithString(levelText.c_str(), "soupofjustice_42_white.fnt");
  levelLabel->setPosition(ccp(screenSize.width/2, 240));
  addChild(levelLabel);
  
  float scaleTime = 0.1f;
  CCFiniteTimeAction* sequence = CCSequence::actions
  (
   CCScaleTo::actionWithDuration(scaleTime, 1.2f),
   CCScaleTo::actionWithDuration(scaleTime, 1.0f),
   CCCallFunc::actionWithTarget(this, callfunc_selector(LevelEndView::showCoins)),
   NULL
  );
  levelLabel->runAction(sequence);
}

void LevelEndView::showCoins() {
  String coinFile = (coins_ > 0) ? "level_end_coin.png" : "level_end_coin_blank.png";
  CCSprite* coinSprite = CCSprite::spriteWithSpriteFrameName(coinFile.c_str());
  coinSprite->setPosition(ccp(190, 190));
  addChild(coinSprite);
  
  float scaleTime = 0.1;
  
  CCFiniteTimeAction* coinSequence = CCSequence::actions
  (
   CCScaleTo::actionWithDuration(scaleTime, 1.2),
   CCScaleTo::actionWithDuration(scaleTime, 1.0),
   CCCallFunc::actionWithTarget(this, callfunc_selector(LevelEndView::showCoin2)),
   NULL
  );
  
  coinSprite->runAction(coinSequence);
  
  if (coins_ > 0) {  
    String coinAwardEffect = String::withFormat("coin_award%d", coinAwardIndex_++);
    SoundSystem::sharedSoundSystem()->playEffect(coinAwardEffect);
  } 
}

void LevelEndView::showCoin2() {
  String coinFile = (coins_ > 1) ? "level_end_coin.png" : "level_end_coin_blank.png";
  CCSprite* coinSprite = CCSprite::spriteWithSpriteFrameName(coinFile.c_str());
  coinSprite->setPosition(ccp(240, 190));
  addChild(coinSprite);
  
  float scaleTime = 0.1;
  
  CCFiniteTimeAction* coinSequence = CCSequence::actions
  (
   CCScaleTo::actionWithDuration(scaleTime, 1.2),
   CCScaleTo::actionWithDuration(scaleTime, 1.0),
   CCCallFunc::actionWithTarget(this, callfunc_selector(LevelEndView::showCoin3)),
   NULL
  );
  
  coinSprite->runAction(coinSequence);
  if (coins_ > 1) {
    String coinAwardEffect = String::withFormat("coin_award%d", coinAwardIndex_++);
    SoundSystem::sharedSoundSystem()->playEffect(coinAwardEffect);
  }
}

void LevelEndView::showCoin3() {
  String coinFile = (coins_ > 2) ? "level_end_coin.png" : "level_end_coin_blank.png";
  CCSprite* coinSprite = CCSprite::spriteWithSpriteFrameName(coinFile.c_str());
  coinSprite->setPosition(ccp(290, 190));
  addChild(coinSprite);
  
  float scaleTime = 0.1;
  
  CCFiniteTimeAction* coinSequence = CCSequence::actions
  (
   CCScaleTo::actionWithDuration(scaleTime, 1.2),
   CCScaleTo::actionWithDuration(scaleTime, 1.0),
   CCCallFunc::actionWithTarget(this, callfunc_selector(LevelEndView::showTime)),
   NULL
  );
  
  coinSprite->runAction(coinSequence);
  
  if (coins_ > 2) {  
    String coinAwardEffect = String::withFormat("coin_award%d", coinAwardIndex_++);
    SoundSystem::sharedSoundSystem()->playEffect(coinAwardEffect);
  }
}

void LevelEndView::showTime() {
  CCLabelBNFont* timeLabel = CCLabelBNFont::labelWithString("Time: 0 secs", "soupofjustice_28_white.fnt");
  timeLabel->setPosition(ccp(240, 140));
  addChild(timeLabel);
  
  TimeCountUpAction* countUp = TimeCountUpAction::actionWithCount(time_, timeLabel, 0.1f, 1);
  CCCallFunc* showcore = CCCallFunc::actionWithTarget(this, callfunc_selector(LevelEndView::showScore));
  CCSequence* sequence = CCSequence::actionOneTwo(countUp, showcore);
  timeLabel->runAction(sequence);
}

void LevelEndView::showScore() {
  CCSize screenSize = CCDirector::sharedDirector()->getWinSize();
  CCLabelBNFont* scoreLabel = CCLabelBNFont::labelWithString("Score: 0", "soupofjustice_36_white.fnt");
  scoreLabel->setPosition(ccp(screenSize.width/2, 100));
  addChild(scoreLabel);
  
  int blipInterval = score_ < 1000 ? 100 : 1000;
  ScoreCountUpAction* countUp = ScoreCountUpAction::actionWithCount(score_, scoreLabel, 0.5f, blipInterval);
  
  scoreLabel->runAction(countUp);
}
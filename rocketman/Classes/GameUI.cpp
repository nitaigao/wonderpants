#include "GameUI.h"

#include "cocos2d.h"
USING_NS_CC;

#include "GameScene.h"
#include "BoostBar.h"

#include "SString.h"
#include "CClabelBNFont.h"

static const int TAG_BOOST = 100;

GameUI* GameUI::nodeWithController(GameScene* controller, int chapter, int level) {
  GameUI* ui = new GameUI();
  ui->initWithController(controller, chapter, level);
  ui->autorelease();
  return ui;
}

bool GameUI::initWithController(GameScene* controller, int chapter, int level) {
  {
    CCMenu* gameplay = CCMenu::node();
        
    {
      CCSprite* up = CCSprite::spriteWithSpriteFrameName("reset_button.png");
      CCSprite* down = CCSprite::spriteWithSpriteFrameName("reset_button_pressed.png");
      CCMenuItemSprite* restartButton = CCMenuItemSprite::itemFromNormalSprite(up, down, controller, menu_selector(GameScene::restartGame));    
      gameplay->addChild(restartButton, 0);
    }
    
    {
      CCSprite* up = CCSprite::spriteWithSpriteFrameName("pause_button.png");
      CCSprite* down = CCSprite::spriteWithSpriteFrameName("pause_button_pressed.png");
      CCMenuItemSprite* pauseButton = CCMenuItemSprite::itemFromNormalSprite(up, down, controller, menu_selector(GameScene::pauseGame));    
      gameplay->addChild(pauseButton, 0);
    }
    
    {
      BoostBar* boostBar = BoostBar::node();
      CCSize screenSize = CCDirector::sharedDirector()->getWinSize();
      boostBar->setPosition(ccp(110, screenSize.height - 20));
      this->addChild(boostBar, boostBar->getZOrder(), TAG_BOOST);
    }
    
    {
      CCSize screenSize = CCDirector::sharedDirector()->getWinSize();
      
      String levelString = String::withFormat("%d - %d", chapter + 1, level + 1);
      CCLabelBNFont* levelLabel = CCLabelBNFont::labelWithString(levelString.c_str(), "soupofjustice_24_white.fnt");
      levelLabel->setPosition(ccp(screenSize.width - 30, -10));
      addChild(levelLabel);
      
      CCDelayTime* delayIn = CCDelayTime::actionWithDuration(2);
      CCMoveBy* moveUp = CCMoveBy::actionWithDuration(0.4, ccp(0, 25));
      CCEaseBackOut* moveUpEase = CCEaseBackOut::actionWithAction(moveUp);
      
      CCFiniteTimeAction* sequence = CCSequence::actions(delayIn, moveUpEase, 0);
      levelLabel->runAction(sequence);
    }
    
    {
      CCSize screenSize = CCDirector::sharedDirector()->getWinSize();
      gameplay->setPosition(ccp(screenSize.width - 50, screenSize.height - 20));
      gameplay->alignItemsHorizontallyWithPadding(-10);
      this->addChild(gameplay);
    }
  }
  
  return true;
}

void GameUI::setBoost(float boost) {
  BoostBar* boostBar = (BoostBar*)getChildByTag(TAG_BOOST);
  boostBar->setBoost(boost);
}
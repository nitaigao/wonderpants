#include "LevelSceneView.h"

#include "Common.h"

#include "CClabelBNFont.h"
#include "cocos2d.h"
USING_NS_CC;

#include "SaveGame.h"
#include "ChapterData.h"
#include "BackButton.h"
#include "GameConfig.h"

#include "LevelsScene.h"

LevelSceneView* LevelSceneView::nodeWithController(LevelsScene* controller, const ChapterData& chapterData) {
  LevelSceneView* view = new LevelSceneView();
  view->initWithController(controller, chapterData);
  view->autorelease();
  return view;
}

void LevelSceneView::initWithController(LevelsScene* controller, const ChapterData& chapterData) {
  {
    CCSprite* background = CCSprite::spriteWithSpriteFrameName(chapterData.background().c_str());
    CCSize screenSize = CCDirector::sharedDirector()->getWinSize();
    background->setPosition(ccp(screenSize.width / 2, screenSize.height / 2));
    this->addChild(background);
  }
  
  {
    BackButton* back = BackButton::itemWithController(controller, menu_selector(LevelsScene::back));
    this->addChild(back);
  }
  
  {
    CCMenu* menu = CCMenu::node();
    int level = 0;
    for (int row = 0; row < GameConfig::levelRows(); row++) {
      for (int column = 0; column < GameConfig::levelColumns(); column++) {
        CCSprite* up = CCSprite::spriteWithSpriteFrameName("level_frame.png");
        CCSprite* down = CCSprite::spriteWithSpriteFrameName("level_frame_down.png");
        CCSprite* disabled = CCSprite::spriteWithSpriteFrameName("level_frame_disabled.png");
        
        CCSize contentSize = CCSize(up->getContentSize().width + 10, up->getContentSize().height + 15);
        
        CCMenuItemSprite* levelItem = CCMenuItemSprite::itemFromNormalSprite(up, down, disabled, controller, menu_selector(LevelsScene::playLevel));

        {
          bool isEnabled = SaveGame::sharedSaveData()->getProgress(level - 1, chapterData.chapter());
          isEnabled = level == 0 ? true : isEnabled;
          levelItem->setIsEnabled(isEnabled);
        }
        
        {
          int coins = SaveGame::sharedSaveData()->getCoins(level, chapterData.chapter());
          
          const char* coin1Src = (coins > 0) ? "level_frame_coin.png" : "level_frame_coin_blank.png";
          CCSprite* coin1Icon = CCSprite::spriteWithSpriteFrameName(coin1Src);
          coin1Icon->setPosition(ccp((contentSize.width/2)-6, 34));
          levelItem->addChild(coin1Icon);

          const char* coin2Src = (coins > 1) ? "level_frame_coin.png" : "level_frame_coin_blank.png";
          CCSprite* coin2Icon = CCSprite::spriteWithSpriteFrameName(coin2Src);
          coin2Icon->setPosition(ccp((contentSize.width/2)-15, 19));
          levelItem->addChild(coin2Icon);

          const char* coin3Src = (coins > 2) ? "level_frame_coin.png" : "level_frame_coin_blank.png";
          CCSprite* coin3Icon = CCSprite::spriteWithSpriteFrameName(coin3Src);
          coin3Icon->setPosition(ccp((contentSize.width/2)+3, 19));
          levelItem->addChild(coin3Icon);
        }
        
        levelItem->setTag(level++);
        levelItem->setAnchorPoint(ccp(0, 0));
        levelItem->setPosition(ccp(contentSize.width * column, contentSize.height * (GameConfig::levelRows() - row - 1)));
        
        menu->addChild(levelItem, 0);
        
        String labelString = String::withFormat("%d", level);
        CCLabelBNFont* label = CCLabelBNFont::labelWithString(labelString.c_str(), "soupofjustice_18_white.fnt");
        label->setPosition(ccp(up->getContentSize().width - 10, up->getContentSize().height - 10));
        levelItem->addChild(label);
      }
    }
    menu->setPosition(ccp(60, 27));
    this->addChild(menu);
  }
}

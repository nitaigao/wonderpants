#include "ChapterView.h"

#include "cocos2d.h"
USING_NS_CC;

#include "ChapterData.h"
#include "ChaptersScene.h"

#include "CCScrollLayerButton.h"
#include "ChapterUnlockedPriceTag.h"
#include "ChapterLockedPriceTag.h"

#include "CCSpriteCascadeVisible.h"

static const int TAG_COMIC = 100;
static const int TAG_LOCKED_BANNER = 101;

ChapterView::ChapterView() : locked_(false) {
  
}

ChapterView* ChapterView::viewWithData(const ChapterData& data, int score, int coins, ChaptersScene* controller) {
  ChapterView* view = new ChapterView();
  view->initWithData(data, score, coins, controller);
  view->autorelease();
  return view;
}

void ChapterView::initWithData(const ChapterData& data, int score, int coins, ChaptersScene* controller) {

  {
    CCSprite* stacks = CCSprite::spriteWithSpriteFrameName(data.stacks().c_str());
    CCSize screenSize = CCDirector::sharedDirector()->getWinSize();
    stacks->setPosition(ccp((screenSize.width / 2)-145, (screenSize.height / 2)+15));
    this->addChild(stacks);
  }
  {
    target = controller;
    selector = menu_selector(ChaptersScene::selectChapter);
  }
  
  {
    active_ = data.required() > -1;
    locked_ = coins < data.required();
  }

  {
    // this is a work around because the jpg spritesheet's are 50% opacity on the 3gs
    CCSpriteCascadeVisible* up = CCSpriteCascadeVisible::sprite();
    CCSprite* upSprite = CCSprite::spriteWithSpriteFrameName(data.comic().c_str());
    up->setScale(0.95f);
    up->addChild(upSprite, 1);
    
    CCSprite* upBackround = CCSprite::sprite();
    upBackround->setTextureRect(upSprite->getTextureRect());
    upBackround->setColor(ccBLACK);
    upBackround->setScale(0.95f);
    up->addChild(upBackround, 0);
    
    String downFilename = data.comic().replace(".jpg", "_down.png");
    
    CCSpriteCascadeVisible* down = CCSpriteCascadeVisible::sprite();
    CCSprite* downSprite = CCSprite::spriteWithSpriteFrameName(downFilename.c_str());
    downSprite->setScale(0.95f);
    down->addChild(downSprite, 1);
    
    CCSprite* downBackround = CCSprite::sprite();
    downBackround->setTextureRect(downSprite->getTextureRect());
    downBackround->setColor(ccBLACK);
    downBackround->setScale(0.95f);
    down->addChild(downBackround, 0);

    CCScrollLayerButton* comic = CCScrollLayerButton::button(up, down, 0, 0);
    comic->setContentSize(upSprite->getContentSize());
    comic->setTag(TAG_COMIC);

    if (data.required() > -1 && coins >= data.required()) {
      comic->setTarget(this, menu_selector(ChapterView::chapterSelected));
    }
    
    CCSize screenSize = CCDirector::sharedDirector()->getWinSize();
    comic->setPosition(ccp(screenSize.width / 2, (screenSize.height / 2)+15));  
    this->addChild(comic);
  }
  
  {
    if (data.required() > -1) {
      if (coins < data.required()) {
        ChapterUnlockedPriceTag* priceTag = ChapterUnlockedPriceTag::node(data.required());
        CCSize screenSize = CCDirector::sharedDirector()->getWinSize();
        priceTag->setPosition(ccp(screenSize.width / 2, 40));
        this->addChild(priceTag);

        CCSprite* lockedBanner = CCSprite::spriteWithSpriteFrameName("chapter_locked.png");
        lockedBanner->setPosition(ccp(240, 160));
        lockedBanner->setTag(TAG_LOCKED_BANNER);
        addChild(lockedBanner);
      } else {
        ChapterLockedPriceTag* priceTag = ChapterLockedPriceTag::node(score);
        CCSize screenSize = CCDirector::sharedDirector()->getWinSize();
        priceTag->setPosition(ccp(screenSize.width / 2, 40));
        this->addChild(priceTag);
      }
    }
  }
}


void ChapterView::bounceComic() {
  if (!active_) return;
  
  CCNode* comic = getChildByTag(TAG_COMIC);
  bounce(comic, 1.05f);
    
  if (locked_) {
    CCNode* banner = getChildByTag(TAG_LOCKED_BANNER); 
    bounce(banner, 1.06f);
  }
}

void ChapterView::bounce(cocos2d::CCNode* node, float amount) {
  float scaleTime = 0.1;  
  CCDelayTime* delay = CCDelayTime::actionWithDuration(0.4f);  
  CCScaleTo* scaleUp = CCScaleTo::actionWithDuration(scaleTime, amount);
  CCScaleTo* scaleDown = CCScaleTo::actionWithDuration(scaleTime, node->getScale());
  CCFiniteTimeAction* sequence = CCSequence::actions(delay, scaleUp, scaleDown, 0);
  node->runAction(sequence);
}

void ChapterView::chapterSelected(CCNode* sender) {
  if (target) {
    (target->*selector)(this);
  }
}
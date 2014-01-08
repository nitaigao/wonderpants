#include "ChaptersSceneView.h"

#include "cocos2d.h"
USING_NS_CC;

#include "CClabelBNFont.h"

#include "CCScrollLayer.h"

#include "ChaptersScene.h"
#include "ChapterView.h"

#include "SoundSystem.h"

static const int TAG_SCROLL = 100;
static const int TAG_COINS = 101;

ChaptersSceneView* ChaptersSceneView::nodeWithController(ChaptersScene* controller) {
  ChaptersSceneView* view = new ChaptersSceneView();
  view->initWithController(controller);
  view->autorelease();
  return view;
}

void ChaptersSceneView::initWithController(ChaptersScene* controller) {
  {
    chapters = 0;
  }
  {
    CCScrollLayer* scroll = CCScrollLayer::layerWithOffset(175, controller, menu_selector(ChaptersScene::pageChanged));
    this->addChild(scroll, 1, TAG_SCROLL);
  }
  
  {
    CCSize screenSize = CCDirector::sharedDirector()->getWinSize();
    CCSprite* coin = CCSprite::spriteWithSpriteFrameName("level_end_coin.png");
    coin->setPosition(ccp(screenSize.width - 30, screenSize.height - 30));
    addChild(coin, 2);
  }
  {
    CCSize screenSize = CCDirector::sharedDirector()->getWinSize();
    CCLabelBNFont* coinsLabel = CCLabelBNFont::labelWithString("0", "soupofjustice_28_white.fnt", CCTextAlignmentRight);
    coinsLabel->setPosition(ccp(screenSize.width - 55, screenSize.height - 30));

    addChild(coinsLabel, 2, TAG_COINS);
  }
}

void ChaptersSceneView::addChapterView(ChapterView* view) {
  view->setTag(chapters);
  chapters += 1;
  {
    CCSprite* background = CCSprite::spriteWithSpriteFrameName("wood_background.jpg");
    CCSize screenSize = CCDirector::sharedDirector()->getWinSize();
    background->setPosition(ccp((screenSize.width*chapters) - (screenSize.width / 2), screenSize.height / 2));
    this->addChild(background);
  }
  getChildByTag(TAG_SCROLL)->addChild(view);
}

void ChaptersSceneView::setChapter(int chapter) {
  CCScrollLayer* scroll = (CCScrollLayer*)getChildByTag(TAG_SCROLL);
  scroll->setPage(chapter);
}

void ChaptersSceneView::setCoins(int coins) {
  String coinsString = String::withFormat("%i", coins).c_str();
  static_cast<CCLabelBNFont*>(getChildByTag(TAG_COINS))->setString(coinsString.c_str());
}

void ChaptersSceneView::selectChapter(int chapter) {
  static_cast<CCScrollLayer*>(getChildByTag(TAG_SCROLL))->scrollToPage(chapter + 1);
}

void ChaptersSceneView::bounceComic(int chapter) {
  CCNode* child = static_cast<CCScrollLayer*>(getChildByTag(TAG_SCROLL))->getChildByTag(chapter);
  ChapterView* view = static_cast<ChapterView*>(child);
  view->bounceComic();
}
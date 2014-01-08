#include "BoostBar.h"

#include "cocos2d.h"
USING_NS_CC;

static const int TAG_PROGRESS = 100;

BoostBar* BoostBar::node() {
  BoostBar* node = new BoostBar();
  node->init();
  node->autorelease();
  return node;
}

void BoostBar::init() {
  CCSprite* bottomLayer = CCSprite::spriteWithSpriteFrameName("boost_bar_bottom_layer.png");
  bottomLayer->setPosition(ccp(100, 0));
  addChild(bottomLayer);  
  
  //TODO: Make from sprite frame
  CCProgressTimer* progressBar = CCProgressTimer::progressWithFile("boost_bar_colour.png");
  progressBar->setType(kCCProgressTimerTypeHorizontalBarLR);
  progressBar->setPosition(ccp(3, 0));
  addChild(progressBar, progressBar->getZOrder(), TAG_PROGRESS);
  
  CCSprite* topLayer = CCSprite::spriteWithSpriteFrameName("boost_bar_top_layer.png");
  addChild(topLayer);
}

void BoostBar::setBoost(float boost) {
  CCProgressTimer* progressBar = (CCProgressTimer*)getChildByTag(TAG_PROGRESS);
  progressBar->setPercentage(boost*100);
}
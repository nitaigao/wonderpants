#include "EndGameSceneView.h"

#include "cocos2d.h"
USING_NS_CC;

EndGameSceneView* EndGameSceneView::nodeWithController(EndGameScene* controller) {
  EndGameSceneView* node = new EndGameSceneView();
  node->initWithController(controller);
  node->autorelease();
  return node;
}

bool EndGameSceneView::initWithController(EndGameScene* controller) {
  {
    CCSprite* background = CCSprite::spriteWithSpriteFrameName("to_be_continued_screen.jpg");
    CCSize screenSize = CCDirector::sharedDirector()->getWinSize();
    background->setPosition(ccp(screenSize.width / 2, screenSize.height / 2));
    this->addChild(background);
  }
  return true;
}
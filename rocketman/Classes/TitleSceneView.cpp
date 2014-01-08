#include "TitleSceneView.h"

#include "cocos2d.h"
USING_NS_CC;

#include "TitleScene.h"
#include "CClabelBNFont.h"
#include "ButtonLabelMenuItem.h"

TitleSceneView* TitleSceneView::nodeWithController(TitleScene *controller) {
  TitleSceneView* pRet = new TitleSceneView();
  pRet->initWithController(controller);
  pRet->autorelease();
  return pRet;
}

void TitleSceneView::initWithController(TitleScene* controller) {
//  {
//    CCLabelBNFont* font = CCLabelBNFont::labelWithString("HELLO", "soupofjustice_28_white.fnt", CCTextAlignmentRight);
//    CCSize screenSize = CCDirector::sharedDirector()->getWinSize();
//    font->setPosition(ccp(screenSize.width / 2, screenSize.height / 2));
//    addChild(font);
//  }
//  {
//    CCSprite* line = CCSprite::spriteWithFile("line.png");
//    CCSize screenSize = CCDirector::sharedDirector()->getWinSize();
//    line->setPosition(ccp(screenSize.width / 2, screenSize.height / 2));
//    addChild(line);
//  }
//  
//  {
//    CCSprite* line = CCSprite::spriteWithFile("line.png");
//    CCSize screenSize = CCDirector::sharedDirector()->getWinSize();
//    line->setRotation(90);
//    line->setPosition(ccp(screenSize.width / 2, screenSize.height / 2));
//    addChild(line);
//  }

  {
    CCSprite* background = CCSprite::spriteWithSpriteFrameName("Title_page.jpg");
    CCSize screenSize = CCDirector::sharedDirector()->getWinSize();
    background->setPosition(ccp(screenSize.width / 2, screenSize.height / 2));
    this->addChild(background);
  }
  {    
    CCMenuItem* playButton = ButtonLabelMenuItem::itemWithText("Play!", controller, menu_selector(TitleScene::play));
    CCMenuItem* optionsButton = ButtonLabelMenuItem::itemWithText("Options", controller, menu_selector(TitleScene::options)); 
    CCMenu* menu = CCMenu::menuWithItems(playButton, optionsButton, 0);
    
    CCSize screenSize = CCDirector::sharedDirector()->getWinSize();
    CCPoint position = ccp(screenSize.width / 2, 65);
    menu->setPosition(position);
    menu->alignItemsVerticallyWithPadding(10);
    this->addChild(menu);
  } 
}
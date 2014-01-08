#include "PauseSceneView.h"

#include "cocos2d.h"
USING_NS_CC;

#include "SoundControlsMenuItem.h"
#include "ButtonLabelMenuItem.h"

#include "PauseScene.h"

PauseSceneView::~PauseSceneView() {
  CCTouchDispatcher::sharedDispatcher()->removeDelegate(this);
}

PauseSceneView* PauseSceneView::nodeWithController(PauseScene* controller) {
  PauseSceneView* view = new PauseSceneView();
  view->initWithController(controller);
  view->autorelease();
  return view;
}

bool PauseSceneView::initWithController(PauseScene* controller) {
  
  {
    CCSprite* glassPanel = CCSprite::sprite();
    glassPanel->setOpacity(0);
    CCSize screenSize = CCDirector::sharedDirector()->getWinSize();
    glassPanel->setTextureRect(CCRectMake(0, 0, screenSize.width, screenSize.height));
    addChild(glassPanel);
  }
  
  {
    CCTouchDispatcher::sharedDispatcher()->addTargetedDelegate(this, 0, true);
  }
  
  {
    CCMenu* menu = CCMenu::node();
    
    {
      SoundControlsMenuItem* sound = SoundControlsMenuItem::node();
      menu->addChild(sound, 0);
    }
    
    {
      ButtonLabelMenuItem* resume = ButtonLabelMenuItem::itemWithText("Resume", controller, menu_selector(PauseScene::resumeGame));
      menu->addChild(resume, 0);
    }
    
    {
      ButtonLabelMenuItem* levels = ButtonLabelMenuItem::itemWithText("Level Select", controller, menu_selector(PauseScene::levelSelect));
      menu->addChild(levels, 0);
    }
    
    {
      ButtonLabelMenuItem* chapters = ButtonLabelMenuItem::itemWithText("Main Menu", controller, menu_selector(PauseScene::chapterSelect));
      menu->addChild(chapters, 0);      
    }
    
    menu->alignItemsVerticallyWithPadding(10);
    this->addChild(menu);
  }
  
  return true;
}

bool PauseSceneView::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent) {
  return true;
}
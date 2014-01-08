#include "OptionsSceneView.h"

#include "cocos2d.h"
USING_NS_CC;

#include "SoundControlsMenuItem.h"
#include "OptionsScene.h"
#include "ButtonLabelMenuItem.h"
#include "BackButton.h"

OptionsSceneView* OptionsSceneView::nodeWithController(OptionsScene* controller) {
  OptionsSceneView* pRet = new OptionsSceneView();
  pRet->initWithController(controller);
  pRet->autorelease();
  return pRet;
}

void OptionsSceneView::initWithController(OptionsScene* controller) {
  {
    CCSprite* background = CCSprite::spriteWithSpriteFrameName("options_screen.jpg");
    CCSize screenSize = CCDirector::sharedDirector()->getWinSize();
    background->setPosition(ccp(screenSize.width / 2, screenSize.height / 2));
    this->addChild(background);
  }
  
  {
    BackButton* back = BackButton::itemWithController(controller, menu_selector(OptionsScene::back));
    this->addChild(back);
  }
  
  {
    
    CCMenu* menu = CCMenu::node();
    CCSize screenSize = CCDirector::sharedDirector()->getWinSize();
  
    {
      SoundControlsMenuItem* soundControls = SoundControlsMenuItem::node(); 
      menu->addChild(soundControls, 0);
    }
    
    
    {
      ButtonLabelMenuItem* reset = ButtonLabelMenuItem::itemWithText("Reset Game", controller, menu_selector(OptionsScene::resetGame));
      menu->addChild(reset, 0);
    }
    
    {
      ButtonLabelMenuItem* reset = ButtonLabelMenuItem::itemWithText("Flip Screen", controller, menu_selector(OptionsScene::flipScreen));
      menu->addChild(reset, 0);
    }
    
    {
      ButtonLabelMenuItem* credits = ButtonLabelMenuItem::itemWithText("Credits", controller, menu_selector(OptionsScene::credits));
      menu->addChild(credits, 0);
    }

    menu->alignItemsVerticallyWithPadding(10);    
    menu->setPosition(ccp(screenSize.width - 160, menu->getPosition().y));
    
    this->addChild(menu);
  }
  
#ifdef CHEATS
  {
    ButtonLabelMenuItem* cheatsButton = ButtonLabelMenuItem::itemWithText("cheats", controller, menu_selector(OptionsScene::cheats));
    CCMenu* cheatsMenu = CCMenu::menuWithItem(cheatsButton);
    cheatsButton->setOpacity(0);
    cheatsMenu->setPosition(ccp(100, 100));
    addChild(cheatsMenu);
  }
#endif
}
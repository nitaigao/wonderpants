#include "CreditsSceneView.h"

#include "Common.h"

#include "cocos2d.h"
USING_NS_CC;

#include "BackButton.h"
#include "CreditsScene.h"
#include "CCMenuItemBNFont.h"

CreditsSceneView* CreditsSceneView::nodeWithController(CreditsScene* controller) {
  CreditsSceneView* view = new CreditsSceneView();
  view->initWithController(controller);
  view->autorelease();
  return view;
}

void CreditsSceneView::initWithController(CreditsScene* controller) {
  {
    CCSprite* background = CCSprite::spriteWithSpriteFrameName("options_screen.jpg");
    CCSize screenSize = CCDirector::sharedDirector()->getWinSize();
    background->setPosition(ccp(screenSize.width / 2, screenSize.height / 2));
    this->addChild(background);
  }
  
  {
    BackButton* back = BackButton::itemWithController(controller, menu_selector(CreditsScene::back));
    this->addChild(back);
  }
  
  {
    
    CCMenu* credits = CCMenu::node();
    
    int creditsHeight = 0;
  
    {
      CCMenuItemBNFont* title = CCMenuItemBNFont::itemWithString("Wonder Pants", "soupofjustice_36_white.fnt");
      creditsHeight += title->getContentSize().height;
      credits->addChild(title, 0);
    }
    
    {
      CCMenuItem* space = CCMenuItemBNFont::itemWithString("", "soupofjustice_36_white.fnt");
      creditsHeight += space->getContentSize().height;
      credits->addChild(space, 0);
    }
    
    {
      std::string creditsPath = CCFileUtils::fullPathFromRelativePath("credits.txt");
      String creditsText = String::fromFile(creditsPath);
      
      for (const String& line : creditsText.lines()) {
        if (line.length() == 0) {
          CCMenuItem* space = CCMenuItemBNFont::itemWithString(" ", "soupofjustice_36_white.fnt");
          creditsHeight += space->getContentSize().height;
          credits->addChild(space, 0);
          continue;
        }
        
        if (line.startsWith("*")) {
          CCMenuItem* title = CCMenuItemBNFont::itemWithString(line.replace("*", "").c_str(), "soupofjustice_24_white.fnt");
          creditsHeight += title->getContentSize().height;
          credits->addChild(title, 0);          
          continue;
        }

        CCMenuItem* text = CCMenuItemBNFont::itemWithString(line.c_str(), "soupofjustice_18_white.fnt");
        creditsHeight += text->getContentSize().height;
        credits->addChild(text, 0);        
      }
    }
    
    CCSize screenSize = CCDirector::sharedDirector()->getWinSize();
    credits->setPosition(ccp(screenSize.width - 160, credits->getPosition().y));
    credits->alignItemsVertically();
    CCPoint position = ccp(credits->getPosition().x, (-creditsHeight) + (screenSize.height / 2.0f));
    credits->setPosition(position);
    this->addChild(credits);
    
    
    CCMoveBy* move = CCMoveBy::actionWithDuration(60, ccp(0, creditsHeight * 2));
    CCMoveTo* reset = CCMoveTo::actionWithDuration(0, position);
    CCSequence* scroll = CCSequence::actionOneTwo(move, reset);
    CCRepeatForever* repeatMove = CCRepeatForever::actionWithAction(scroll);
    credits->runAction(repeatMove);
  }
}

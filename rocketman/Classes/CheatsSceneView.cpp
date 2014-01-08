#include "CheatsSceneView.h"

#include "ButtonLabelMenuItem.h"
#include "BackButton.h"

USING_NS_CC;

#include "CheatsScene.h"

CheatsSceneView* CheatsSceneView::nodeWithController(CheatsScene* controller) {
  CheatsSceneView* node = new CheatsSceneView();
  node->initWithController(controller);
  node->autorelease();
  return node;
}

void CheatsSceneView::initWithController(CheatsScene* controller) {
  
  {
    ButtonLabelMenuItem* chapter1Button = ButtonLabelMenuItem::itemWithText("Unlock CH1", controller, menu_selector(CheatsScene::unlockChapter1));
    ButtonLabelMenuItem* chapter2Button = ButtonLabelMenuItem::itemWithText("Unlock CH2", controller, menu_selector(CheatsScene::unlockChapter2));
    ButtonLabelMenuItem* chapter3Button = ButtonLabelMenuItem::itemWithText("Unlock CH3", controller, menu_selector(CheatsScene::unlockChapter3));
    
    CCMenu* cheatsMenu = CCMenu::menuWithItems(chapter1Button, chapter2Button, chapter3Button, NULL);
    cheatsMenu->alignItemsVerticallyWithPadding(10);
    addChild(cheatsMenu);
  }  
  
  {
    BackButton* back = BackButton::itemWithController(controller, menu_selector(CheatsScene::back));
    addChild(back);
  }
}
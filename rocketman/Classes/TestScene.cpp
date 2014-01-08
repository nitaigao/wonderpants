#include "TestScene.h"

#include "cocos2d.h"
USING_NS_CC;


TestScene* TestScene::scene() {
  TestScene* scene = new TestScene();
  scene->init();
  scene->autorelease();
  return scene;
}

bool TestScene::init() {
  {
    CCMenu* gameplay = CCMenu::node();
    addChild(gameplay);
    
    {
      CCSize screenSize = CCDirector::sharedDirector()->getWinSize();
      gameplay->setPosition(ccp(screenSize.width - 50, screenSize.height - 20));
      gameplay->alignItemsHorizontallyWithPadding(-10);
    }
    
    CCSprite* up = CCSprite::spriteWithSpriteFrameName("reset_button.png");
    CCSprite* down = CCSprite::spriteWithSpriteFrameName("reset_button_pressed.png");
    CCMenuItemSprite* restartButton = CCMenuItemSprite::itemFromNormalSprite(up, down, this, menu_selector(TestScene::reload));    
    gameplay->addChild(restartButton, 0);
    
  }
  
  return true;
}

void TestScene::reload() {
  CCDirector::sharedDirector()->replaceScene(TestScene::scene());
}
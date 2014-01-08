#include "LevelButton.h"

USING_NS_CC;
#include "LevelsScene.h"

LevelButton* LevelButton::node(LevelsScene* controller, int level) {
  LevelButton* node = new LevelButton();
  node->init(controller, level);
  node->autorelease();
  return node;
}

bool LevelButton::init(LevelsScene* controller, int level) {
  CCSprite* up = CCSprite::spriteWithSpriteFrameName("level_frame.png");
  CCSprite* down = CCSprite::spriteWithSpriteFrameName("level_frame_down.png");
  CCSprite* disabled = CCSprite::spriteWithSpriteFrameName("level_frame_disabled.png");
  
  CCSize contentSize = CCSize(up->getContentSize().width + 10, up->getContentSize().height + 15);
  setContentSize(contentSize);
  
  CCMenuItemSprite* levelItem = CCMenuItemSprite::itemFromNormalSprite(up, down, disabled, controller, menu_selector(LevelsScene::playLevel));
  levelItem->setTag(level);
//  levelItem->setAnchorPoint(ccp(0, 0));
  CCMenu* menu = CCMenu::menuWithItem(levelItem);
  addChild(menu);
//  
//  String labelString = String::withFormat("%d", level);
//  CCLabelBNFont* label = CCLabelBNFont::labelWithString(labelString.c_str(), "soupofjustice_18_white.fnt");
//  label->setPosition(ccp(up->getContentSize().width - 10, up->getContentSize().height - 10));
//  levelItem->addChild(label);
  return true;
}


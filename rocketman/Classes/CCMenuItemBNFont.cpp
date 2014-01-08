#include "CCMenuItemBNFont.h"

#include "cocos2d.h"
USING_NS_CC;

#include "CClabelBNFont.h"

CCMenuItemBNFont* CCMenuItemBNFont::itemWithString(const char* text, const char* fntFile) {
  CCMenuItemBNFont* item = new CCMenuItemBNFont();
  item->initWithString(text, fntFile);
  item->autorelease();
  return item;
}

void CCMenuItemBNFont::initWithString(const char* text, const char* fntFile) {
  initWithTarget(0, 0);
  
  CCLabelBNFont* font = CCLabelBNFont::labelWithString(text, fntFile);
  font->setAnchorPoint(ccp(0, 0));
  this->addChild(font);
  
  this->setContentSize(font->getContentSize());
}
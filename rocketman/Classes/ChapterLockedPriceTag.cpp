#include "ChapterLockedPriceTag.h"

#include "CClabelBNFont.h"
#include "Common.h"

ChapterLockedPriceTag* ChapterLockedPriceTag::node(int score) {
  ChapterLockedPriceTag* node = new ChapterLockedPriceTag();
  node->init(score);
  node->autorelease();
  return node;
}

bool ChapterLockedPriceTag::init(int score) {
  CCSprite* background = CCSprite::spriteWithSpriteFrameName("wide_tag.png");
  addChild(background);
  
  CCLabelBNFont* scorePrefixLabel = CCLabelBNFont::labelWithString("SCORE:", "soupofjustice_18_red.fnt");
  scorePrefixLabel->setPosition(ccp(0, 11));
  addChild(scorePrefixLabel);
  
  String scoreString = String::withFormat("%i", score);
  CCLabelBNFont* scoreLabel = CCLabelBNFont::labelWithString(scoreString.c_str(), "soupofjustice_24_red.fnt");
  scoreLabel->setPosition(ccp(0, -6));
  addChild(scoreLabel);
  
  return true;
}


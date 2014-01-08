#include "ChapterUnlockedPriceTag.h"

#include "CClabelBNFont.h"
#include "Common.h"

ChapterUnlockedPriceTag* ChapterUnlockedPriceTag::node(int required) {
  ChapterUnlockedPriceTag* node = new ChapterUnlockedPriceTag();
  node->init(required);
  node->autorelease();
  return node;
}

bool ChapterUnlockedPriceTag::init(int required) {
  CCSprite* background = CCSprite::spriteWithSpriteFrameName("wide_tag.png");
  addChild(background);
  
  String priceString = String::withFormat("%i", required);
  CCLabelBNFont* priceLabel = CCLabelBNFont::labelWithString(priceString.c_str(), "soupofjustice_24_red.fnt");
  priceLabel->setPosition(ccp(-15, 3));
  addChild(priceLabel);
  
  CCSprite* coinIcon = CCSprite::spriteWithSpriteFrameName("chapter_coin.png");
  coinIcon->setPosition(ccp(20, 3));
  addChild(coinIcon);
  
  return true;
}


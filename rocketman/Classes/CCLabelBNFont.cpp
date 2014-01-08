#include "CClabelBNFont.h"

#include "cocos2d.h"

#include "CCLabelBMFont.h"
USING_NS_CC;

#include "String.h"

CCLabelBNFont::~CCLabelBNFont() {
  m_pConfiguration->release();
}

CCLabelBNFont* CCLabelBNFont::labelWithString(const char* str, const char* fntFile, CCTextAlignment alignment, int linePadding) {
  CCLabelBNFont *pRet = new CCLabelBNFont();
  if(pRet && pRet->initWithString(str, fntFile, alignment, linePadding))
  {
    pRet->autorelease();
    return pRet;
  }
  CC_SAFE_DELETE(pRet);
  return NULL;
}

CCLabelBNFont* CCLabelBNFont::labelWithString(const char* str, const char* fntFile, cocos2d::CCTextAlignment alignment) {
  return labelWithString(str, fntFile, alignment, 5);
}

CCLabelBNFont *CCLabelBNFont::labelWithString(const char *str, const char *fntFile) {
  return labelWithString(str, fntFile, CCTextAlignmentCenter);
}

bool CCLabelBNFont::initWithString(const char *theString, const char *fntFile, cocos2d::CCTextAlignment alignment, int linePadding) {	
  m_Alignment = alignment;
  m_linePadding = linePadding;
  m_pConfiguration = FNTConfigLoadFile(fntFile);
  m_pConfiguration->retain();
  CCAssert( m_pConfiguration, "Error creating config for LabelBNFont");
  
  spriteFrame_ = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(m_pConfiguration->m_sAtlasName.c_str());
  
  if (spriteFrame_) {
    CCSprite::setOpacity(255);
    setAnchorPoint(ccp(0.5f, 0.5f));
    m_tContentSize = CCSizeZero;    
    this->setString(theString);
    
    return true;
  }
  return false;
}

CCSprite* CCLabelBNFont::createLine(const String& line) {
  CCSprite* lineContainer = CCSprite::sprite();
  lineContainer->setAnchorPoint(ccp(0, 0));
  
  unsigned int stringLen = line.length();
  
  int xAdvance = 0;
  for(unsigned int i = 0; i < stringLen; i++) {
    unsigned char c = line.charAt(i);
    
    const ccBMFontDef& fontDef = m_pConfiguration->m_pBitmapFontArray[c];
    
    CCRect rect = fontDef.rect;
    rect.origin.x /= CC_CONTENT_SCALE_FACTOR();
    rect.origin.y /= CC_CONTENT_SCALE_FACTOR();
    rect.size.width /= CC_CONTENT_SCALE_FACTOR();
    rect.size.height /= CC_CONTENT_SCALE_FACTOR();
    
    rect.origin.x += spriteFrame_->getRect().origin.x;
    rect.origin.y += spriteFrame_->getRect().origin.y;
    
    CCSprite* charSprite = CCSprite::spriteWithTexture(spriteFrame_->getTexture(), rect);
    
    int charY = m_pConfiguration->m_uCommonHeight - fontDef.rect.size.height - fontDef.yOffset;
    int charX = fontDef.xOffset + xAdvance;
    
    charY /= CC_CONTENT_SCALE_FACTOR();
    
    charSprite->setAnchorPoint(ccp(0, 0));
    charSprite->setPosition(ccp(charX, charY));
    charSprite->setOpacity(m_nOpacity);
    
    lineContainer->addChild(charSprite);
    
    xAdvance += fontDef.xAdvance / CC_CONTENT_SCALE_FACTOR();
  }

  lineContainer->setContentSize(CCSize(xAdvance, m_pConfiguration->m_uCommonHeight / CC_CONTENT_SCALE_FACTOR()));       
  
  return lineContainer;
}

void CCLabelBNFont::createFontChars() {
  this->removeAllChildrenWithCleanup(true);
  
  Array<String> lines = String(string_).lines();
  Array<String> reversedLines = lines.reverse();
  
  CCSprite* allLines = CCSprite::sprite();
  addChild(allLines);
  
  int totalHeight = 0;
  int totalWidth = 0;
  int lineIndex = 0;
  int nextY = 0;

  for (const String& line : reversedLines) {
    CCSprite* lineContainer = createLine(line);
    allLines->addChild(lineContainer);
    
    lineContainer->setPosition(ccp(0, nextY));
    
    int lineWidth = lineContainer->getContentSize().width;
    if (lineWidth > totalWidth) {
      totalWidth = lineWidth;
    }
    
    totalHeight += lineContainer->getContentSize().height / CC_CONTENT_SCALE_FACTOR();
    
    lineIndex++;
    
    nextY = lineContainer->getContentSize().height * lineIndex;
    
    if (lineIndex < reversedLines.count()) {
      nextY += m_linePadding;
      totalHeight += m_linePadding;
    }
  }
  
  allLines->setContentSize(CCSize(totalWidth, totalHeight * CC_CONTENT_SCALE_FACTOR()));
  setContentSize(allLines->getContentSize());
  
  // second pass - set x pos according to alignment
  if (m_Alignment == CCTextAlignmentCenter) {    
    CCObject* pObject = NULL;
    CCARRAY_FOREACH(allLines->getChildren(), pObject) {
      CCNode* pChild = (CCNode*) pObject;
      if (pChild) {
        int width = pChild->getContentSizeInPixels().width  / CC_CONTENT_SCALE_FACTOR();
        int x = (totalWidth - width) / 2.0f;
        int y = pChild->getPosition().y;
        pChild->setPosition(ccp(x, y));
      }
    }
    allLines->setPosition(ccp(allLines->getContentSize().width/2.0f, 
                              allLines->getContentSize().height/2.0f));
  }
  
  if (m_Alignment == CCTextAlignmentRight) {
    CCObject* pObject = NULL;
    CCARRAY_FOREACH(allLines->getChildren(), pObject) {
      CCNode* pChild = (CCNode*) pObject;
      if (pChild) {
        int width = pChild->getContentSizeInPixels().width / CC_CONTENT_SCALE_FACTOR(); 
        int x = (totalWidth - width)/CC_CONTENT_SCALE_FACTOR();
        int y = pChild->getPosition().y;
        pChild->setPosition(ccp(x / CC_CONTENT_SCALE_FACTOR(), y / CC_CONTENT_SCALE_FACTOR()));
      }
    }
    allLines->setPosition(ccp(0, (allLines->getContentSizeInPixels().height/2.0f)/CC_CONTENT_SCALE_FACTOR()));
  }
  
  if (m_Alignment == CCTextAlignmentLeft) {
    allLines->setPosition(ccp(allLines->getContentSizeInPixels().width, allLines->getContentSizeInPixels().height/2.0f));
  }
}

void CCLabelBNFont::setString(const char *label) {
  string_ = label;
  this->createFontChars();
}

const char* CCLabelBNFont::getString() {
  return string_.c_str();
}

void CCLabelBNFont::setOpacity(GLubyte opacity) {
  CCSprite::setOpacity(opacity);
  
  // change the opacity of the characters - which at allLines->line->character
  CCObject* allLinesObject = m_pChildren->objectAtIndex(0);
  CCSprite* allLines = static_cast<CCSprite*>(allLinesObject);  
  
  for (int lineIndex = 0; lineIndex < allLines->getChildren()->count(); lineIndex++) {
    CCObject* lineObject = allLines->getChildren()->objectAtIndex(lineIndex);
    CCSprite* line = static_cast<CCSprite*>(lineObject);
    
    for (int charIndex = 0; charIndex < line->getChildren()->count(); charIndex++) {
      CCObject* charObject = line->getChildren()->objectAtIndex(charIndex);
      CCSprite* charSprite = static_cast<CCSprite*>(charObject);
      charSprite->setOpacity(opacity);
    }
  }
}
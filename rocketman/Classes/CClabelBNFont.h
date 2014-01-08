#ifndef __CC_LABEL_BN_FONT_H
#define __CC_LABEL_BN_FONT_H

#include "CCSprite.h"
#include "CCProtocols.h"

#include "CCLabelBMFont.h"
#include "SString.h"

class CCLabelBNFont : public cocos2d::CCSprite, public cocos2d::CCLabelProtocol {
  
public:
  
  ~CCLabelBNFont();
  
public:
  
  static CCLabelBNFont* labelWithString(const char* string, const char* fntFile, cocos2d::CCTextAlignment alignment);
  
  static CCLabelBNFont* labelWithString(const char* string, const char* fntFile, cocos2d::CCTextAlignment alignment, int linePadding);
  
  static CCLabelBNFont* labelWithString(const char* string, const char* fntFile);
  
  bool initWithString(const char *theString, const char *fntFile, cocos2d::CCTextAlignment alignment, int linePadding);
  
  void setString(const char *label);
  
  const char* getString(void);
  
  void setOpacity(GLubyte opacity);
    
private:
  
  void createFontChars();
  cocos2d::CCSprite* createLine(const String& lineText);
  
private:

  cocos2d::CCSpriteFrame* spriteFrame_;
  
  std::string string_;;

  cocos2d::CCBMFontConfiguration *m_pConfiguration;
  
  cocos2d::CCTextAlignment m_Alignment;
  
  int m_linePadding;

};

#endif

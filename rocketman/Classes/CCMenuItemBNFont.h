#ifndef CCMenuItemBNFont_H_
#define CCMenuItemBNFont_H_

#include "CCMenuItem.h" 

class CCMenuItemBNFont : public cocos2d::CCMenuItem {
  
public:
  
  static CCMenuItemBNFont* itemWithString(const char* text, const char* fntFile);
  
  void initWithString(const char* text, const char* fntFile);
  
  
};

#endif

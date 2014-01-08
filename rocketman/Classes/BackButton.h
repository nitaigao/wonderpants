#ifndef BackButton_H_
#define BackButton_H_

#include "CCNode.h"

class BackButton : public cocos2d::CCNode {
  
public:
  
  static BackButton* itemWithController(cocos2d::SelectorProtocol *controller, cocos2d::SEL_MenuHandler selector);
  
  void initWithController(cocos2d::SelectorProtocol *controller, cocos2d::SEL_MenuHandler selector);
  
private:
  
  void onPushed(cocos2d::CCObject* object);
  
private:
  
  cocos2d::SEL_MenuHandler handler;
  SelectorProtocol* controller;
  
};

#endif

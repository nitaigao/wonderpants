#pragma once
#include "cocos2d.h"
#define TAP_MAX_DRAG 10

using namespace cocos2d;

class CCScrollLayerButton : public CCNode, public CCTargetedTouchDelegate
{
private:
	bool init(CCNode* normalSprite, CCNode* selectedSprite, SelectorProtocol* target, SEL_MenuHandler selector);
	SelectorProtocol* target;
	SEL_MenuHandler selector;
	bool touched;
	CCPoint touchPoint;
public:
	static CCScrollLayerButton* button(CCNode* normalSprite, CCNode* selectedSprite, SelectorProtocol* target, SEL_MenuHandler selector);
  
  void setTarget(SelectorProtocol* target, SEL_MenuHandler selector);
  
	// touch events
	CCRect rect();
	bool containsTouchLocation(CCTouch* touch);
	virtual void onEnter();
	virtual void onExit();
	virtual bool ccTouchBegan(CCTouch* pTouch, CCEvent* pEvent);
	virtual void ccTouchMoved(CCTouch* pTouch, CCEvent* pEvent);
	virtual void ccTouchEnded(CCTouch* pTouch, CCEvent* pEvent);	
  
};

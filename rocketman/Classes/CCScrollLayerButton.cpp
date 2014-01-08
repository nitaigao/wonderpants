#include "CCScrollLayerButton.h"

#include "CCSpriteCascadeVisible.h"

static const int TAG_UP = 100;
static const int TAG_DOWN = 101;

CCScrollLayerButton* CCScrollLayerButton::button(CCNode* normalSprite, CCNode* selectedSprite, SelectorProtocol* target, SEL_MenuHandler selector)
{
	CCScrollLayerButton *pRet = new CCScrollLayerButton();
	if (pRet && pRet->init(normalSprite, selectedSprite, target, selector))
	{
		pRet->autorelease();
		return pRet;
	}
	CC_SAFE_DELETE(pRet)
	return NULL;
}

bool CCScrollLayerButton::init(CCNode* normalSprite, CCNode* selectedSprite, SelectorProtocol* target, SEL_MenuHandler selector)
{
	this->target = target;
	this->selector = selector;
  CCNode::addChild(normalSprite, 0, TAG_UP);
  CCNode::addChild(selectedSprite, 0, TAG_DOWN);
  selectedSprite->setIsVisible(false);
  setContentSize(normalSprite->getContentSize());
	touched = false;
	return true;
}

void CCScrollLayerButton::onEnter()
{
    CCTouchDispatcher::sharedDispatcher()->addTargetedDelegate(this, 0, false);
	CCNode::onEnter();
}

void CCScrollLayerButton::onExit()
{
	CCTouchDispatcher::sharedDispatcher()->removeDelegate(this);
	CCNode::onExit();
}	

CCRect CCScrollLayerButton::rect()
{
	CCSize s = getContentSize();
	return CCRectMake(-s.width / 2, -s.height / 2, s.width, s.height);
}

bool CCScrollLayerButton::containsTouchLocation(CCTouch* touch)
{	
	return CCRect::CCRectContainsPoint(rect(), convertTouchToNodeSpaceAR(touch));
}

bool CCScrollLayerButton::ccTouchBegan(CCTouch* pTouch, CCEvent* pEvent)
{
  if (!target) return false;
  
	if (containsTouchLocation(pTouch) ) 
	{
		touched = true;
		touchPoint = pTouch->locationInView(pTouch->view());
    getChildByTag(TAG_DOWN)->setIsVisible(true);
    getChildByTag(TAG_UP)->setIsVisible(false);
		return true;
	}
	return false;
}

void CCScrollLayerButton::ccTouchMoved(CCTouch* pTouch, CCEvent* pEvent)
{	
  getChildByTag(TAG_DOWN)->setIsVisible(false);
  getChildByTag(TAG_UP)->setIsVisible(true);
}

void CCScrollLayerButton::ccTouchEnded(CCTouch* pTouch, CCEvent* pEvent)
{
	if (touched && target && selector)
	{
		(target->*selector)(this);		
		touched = false;
    getChildByTag(TAG_DOWN)->setIsVisible(false);
    getChildByTag(TAG_UP)->setIsVisible(true);
	}
}

void CCScrollLayerButton::setTarget(SelectorProtocol* target, SEL_MenuHandler selector)  {
  this->target = target;
  this->selector = selector;
}

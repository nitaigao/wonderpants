//  CCScrollLayer.cpp
//  Museum
//
//  Created by GParvaneh on 29/12/2010.
//  Copyright 2010. All rights reserved.
//  Ported to C++ by Lior Tamam on 03/04/2011
#include "CCScrollLayer.h"
#include <time.h>

CCScrollLayer* CCScrollLayer::layerWithOffset(int widthOffset, cocos2d::SelectorProtocol *rec, cocos2d::SEL_MenuHandler pageChangedSelector)
{	
	CCScrollLayer *pRet = new CCScrollLayer();
	if (pRet && pRet->initWithOffset(widthOffset, rec, pageChangedSelector))
	{
		pRet->autorelease();
		return pRet;
	}
	CC_SAFE_DELETE(pRet)
	return NULL;
}

void CCScrollLayer::addChild(cocos2d::CCNode* node) {
  CCLayer::addChild(node);
  int count = getChildren()->count();
  
  for (unsigned int i=0; i<count; i++) {
    CCNode* child = (CCNode*)getChildren()->objectAtIndex(i);
    child->setAnchorPoint(ccp(0,0));
    child->setPosition(ccp((i*scrollWidth),0));
  }
  
  totalScreens = count;
}

bool CCScrollLayer::initWithOffset(int widthOffset, cocos2d::SelectorProtocol *rec, cocos2d::SEL_MenuHandler pageChangedSelector)
{	
  m_pPageChangedSelector = pageChangedSelector;
  m_pPageChangedDelegate = rec;
	if (CCLayer::init()) {		
		// Make sure the layer accepts touches
		CCTouchDispatcher::sharedDispatcher()->addTargetedDelegate(this,0,true);
		
		// Set up the starting variables
		if(!widthOffset)
		{
			widthOffset = 0;
		}	
    
    offset = widthOffset;
		currentScreen = 1;
		
		// offset added to show preview of next/previous screens
		scrollWidth  = (int)CCDirector::sharedDirector()->getWinSize().width - widthOffset;
		scrollHeight = (int)CCDirector::sharedDirector()->getWinSize().height;
		startWidth = scrollWidth;
		startHeight = scrollHeight;
		
		return true;	
	}
	else
	{
		return false;
	}	
}

void CCScrollLayer::setPage(int page) 
{
  currentScreen = page;
  this->setPosition(ccp(-((page-1)*scrollWidth),0));
}

void CCScrollLayer::moveToPage(int page) {
  CCEaseBounce* changePage = CCEaseBounce::actionWithAction(CCMoveTo::actionWithDuration(getScrollSpeed(), ccp(-((page-1)*scrollWidth),0)));
	this->runAction(changePage);
	currentScreen = page;
  
}

int CCScrollLayer::getPage() {
  return currentScreen - 1;
}

void CCScrollLayer::scrollToPage(int page) {
  CCMoveTo* pageMove = CCMoveTo::actionWithDuration(0.8f, ccp(-((page-1)*scrollWidth),0));
  CCFiniteTimeAction* sequence = CCSequence::actions(CCDelayTime::actionWithDuration(1.0f),
                                                     CCEaseBackInOut::actionWithAction(pageMove),
                                                     CCCallFuncO::actionWithTarget(m_pPageChangedDelegate, m_pPageChangedSelector, this)
                                                     , 0);
  
	this->runAction(sequence);
	currentScreen = page;  
}

float CCScrollLayer::getScrollSpeed() {
  return 0.05f;
}

void CCScrollLayer::moveToNextPage() {
	CCEaseBounce* changePage = CCEaseBounce::actionWithAction(CCMoveTo::actionWithDuration(getScrollSpeed(), ccp(-(((currentScreen+1)-1)*scrollWidth),0)));
	
	this->runAction(changePage);
	currentScreen = currentScreen+1;	
  (m_pPageChangedDelegate->*m_pPageChangedSelector)(this);
}

void CCScrollLayer::moveToPreviousPage()
{	
	CCEaseBounce* changePage =CCEaseBounce::actionWithAction(CCMoveTo::actionWithDuration(getScrollSpeed(), ccp(-(((currentScreen-1)-1)*scrollWidth),0)));
	this->runAction(changePage);
	currentScreen = currentScreen-1;	
  (m_pPageChangedDelegate->*m_pPageChangedSelector)(this);
}

void CCScrollLayer::onExit() {
	CCTouchDispatcher::sharedDispatcher()->removeDelegate(this);
	CCLayer::onExit();
}

bool CCScrollLayer::ccTouchBegan(CCTouch *touch, CCEvent *withEvent) {
	CCPoint touchPoint = touch->locationInView(touch->view());
	touchPoint = CCDirector::sharedDirector()->convertToGL(touchPoint);
	
	startSwipe = (int)touchPoint.x;
	return true;
}

void CCScrollLayer::ccTouchMoved(CCTouch *touch, CCEvent *withEvent) {
	CCPoint touchPoint = touch->locationInView(touch->view());
	touchPoint = CCDirector::sharedDirector()->convertToGL(touchPoint);
  
	this->setPosition(ccp((-(currentScreen-1)*scrollWidth)+(touchPoint.x-startSwipe),0));
  
  CCSet cancelledTouches;
  cancelledTouches.addObject(touch);
  CCTouchDispatcher::sharedDispatcher()->touchesCancelled(&cancelledTouches, withEvent);
  
  static_cast<CCTargetedTouchHandler*>(CCTouchDispatcher::sharedDispatcher()->findHandler(this))->addClaimedTouch(touch);
}

void CCScrollLayer::ccTouchEnded(CCTouch *touch, CCEvent *withEvent) {
	CCPoint touchPoint = touch->locationInView(touch->view());
	touchPoint = CCDirector::sharedDirector()->convertToGL(touchPoint);
	
	int newX = (int)touchPoint.x;
		
	if ( (newX - startSwipe) < -scrollWidth / 3 && (currentScreen+1) <= totalScreens )
	{
		this->moveToNextPage();
	}
	else if ( (newX - startSwipe) > scrollWidth / 3 && (currentScreen-1) > 0 )
	{
		this->moveToPreviousPage();
	}
	else
	{
		this->moveToPage(currentScreen);		
	}		
}
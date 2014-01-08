#include "CCCancellableCallfuncND.h"
#include "AnimationCompleteHandler.h"

USING_NS_CC;

CCCancellableCallfuncND::~CCCancellableCallfuncND() {
  CC_SAFE_DELETE(m_pData);
}

CCCancellableCallfuncND::CCCancellableCallfuncND() : m_pData(0) {
  
}

CCCancellableCallfuncND* CCCancellableCallfuncND::actionWithHandler(AnimationCompleteHandler* handler) {
  CCCancellableCallfuncND* pRet = new CCCancellableCallfuncND();

	if (pRet && pRet->initWithHandler(handler)) {
		pRet->autorelease();
		return pRet;
	}
  
	CC_SAFE_DELETE(pRet);
	return NULL;
}

bool CCCancellableCallfuncND::initWithHandler(AnimationCompleteHandler* pHandler) {
  m_pData = pHandler;
  return true;
}

CCObject* CCCancellableCallfuncND::copyWithZone(CCZone* zone) {
	CCZone* pNewZone = NULL;
	CCCancellableCallfuncND* pRet = NULL;
  
	if (zone && zone->m_pCopyObject) {
		//in case of being called at sub class
		pRet = (CCCancellableCallfuncND*) (zone->m_pCopyObject);
	} else {
		pRet = new CCCancellableCallfuncND();
		zone = pNewZone = new CCZone(pRet);
	}
  
  CCActionInstant::copyWithZone(zone);
	pRet->initWithHandler(m_pData->clone());
	CC_SAFE_DELETE(pNewZone);
	return pRet;
}

void CCCancellableCallfuncND::execute() {
  m_pData->animationComplete();
}

void CCCancellableCallfuncND::startWithTarget(CCNode *pTarget) {
  execute();
}
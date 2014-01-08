#include "GrapplingHookRewardSceneView.h"

#include "GrapplingHookRewardScene.h"

#include "cocos2d.h"
USING_NS_CC;

#include "SoundSystem.h"

#include "CClabelBNFont.h"

static const int TAG_CLOUDS1 = 101;
static const int TAG_CLOUDS2 = 102;

GrapplingHookRewardSceneView* GrapplingHookRewardSceneView::nodeWithController(GrapplingHookRewardScene* controller) {
  GrapplingHookRewardSceneView* node = new GrapplingHookRewardSceneView();
  node->initWithController(controller);
  node->autorelease();
  return node;
}

bool GrapplingHookRewardSceneView::initWithController(GrapplingHookRewardScene* controller) {  
  controller_ = controller;
  CCSize screenSize = CCDirector::sharedDirector()->getWinSize();
  
  {
    CCSprite* background = CCSprite::sprite();
    background->setTextureRect(CCRectMake(0, 0, screenSize.width, screenSize.height));
    background->setColor(ccc3(169, 230, 251));
    background->setPosition(ccp(screenSize.width / 2, screenSize.height / 2));
    addChild(background);
  }
  
  {
    CCSprite* clouds = CCSprite::spriteWithSpriteFrameName("clouds.png");
    clouds->setPosition(ccp(screenSize.width / 2, screenSize.height / 2));
    addChild(clouds, clouds->getZOrder(), TAG_CLOUDS1);
  }
  
  {
    CCSprite* clouds = CCSprite::spriteWithSpriteFrameName("clouds.png");
    clouds->setPosition(ccp(screenSize.width + (screenSize.width / 2), screenSize.height / 2));
    addChild(clouds, clouds->getZOrder(), TAG_CLOUDS2);    
  }
  
  {
    CCSprite* character = CCSprite::spriteWithSpriteFrameName("hanging_swing.png");
    character->setPosition(ccp(0 - screenSize.width / 2, screenSize.height));
    addChild(character);
        
    CCDelayTime* characterMoveInDelay = CCDelayTime::actionWithDuration(2);
    CCMoveTo *characterMoveIn = CCMoveTo::actionWithDuration(2.0f, ccp(screenSize.width / 2, screenSize.height / 1.5));  
    CCEaseBackOut *characterMoveInEase = CCEaseBackOut::actionWithAction(characterMoveIn);
    CCCallFuncN *characterFinished = CCCallFuncN::actionWithTarget(this, callfuncN_selector(GrapplingHookRewardSceneView::characterFinished));
    CCFiniteTimeAction* characterSequence = CCSequence::actions(characterMoveInDelay, characterMoveInEase, characterFinished, 0);
    character->runAction(characterSequence);
  }
  
  {
    this->scheduleUpdate();    
    SoundSystem::sharedSoundSystem()->playMusic("title");
  }
  
  return true;
}

void GrapplingHookRewardSceneView::update(ccTime dt) {
  CCSize screenSize = CCDirector::sharedDirector()->getWinSize();
  
  CCNode* clouds1 = getChildByTag(TAG_CLOUDS1);
  clouds1->setPosition(ccpAdd(clouds1->getPosition(), ccp(-(100 * dt), 0)));
  if (clouds1->getPosition().x <= 0 - (screenSize.width / 2)) {
    clouds1->setPosition(ccp(screenSize.width + (screenSize.width / 2), screenSize.height / 2));
  }
  
  CCNode* clouds2 = getChildByTag(TAG_CLOUDS2);
  clouds2->setPosition(ccpAdd(clouds2->getPosition(), ccp(-(100 * dt), 0)));
  if (clouds2->getPosition().x <= 0 - (screenSize.width / 2)) {
    clouds2->setPosition(ccp(screenSize.width + (screenSize.width / 2), screenSize.height / 2));
  }
}

void GrapplingHookRewardSceneView::characterFinished() {
  CCSize screenSize = CCDirector::sharedDirector()->getWinSize();
  
  CCLabelBNFont* message = CCLabelBNFont::labelWithString("Grappling Hook Unlocked!", "soupofjustice_36_white.fnt");
  message->setPosition(ccp(screenSize.width/2, screenSize.height - (screenSize.height / 7)));
  message->setScale(0.1);
  message->setOpacity(255);
  addChild(message);
  
  CCScaleTo* scaleMessage = CCScaleTo::actionWithDuration(0.7, 1.0);
  CCEaseBackOut* messageEase = CCEaseBackOut::actionWithAction(scaleMessage);
  CCCallFuncN* messageFinished = CCCallFuncN::actionWithTarget(this, callfuncN_selector(GrapplingHookRewardSceneView::messageFinished));
  
  CCFiniteTimeAction* sequence = CCSequence::actions(messageEase, messageFinished, 0);
  message->runAction(sequence);
}

void GrapplingHookRewardSceneView::messageFinished() {
  CCSize screenSize = CCDirector::sharedDirector()->getWinSize();
  CCLabelBNFont* continueMessage = CCLabelBNFont::labelWithString("tap to continue", "soupofjustice_18_white.fnt");
  continueMessage->setOpacity(0);
  continueMessage->setPosition(ccp(screenSize.width - (screenSize.width / 5), screenSize.height/15));
  addChild(continueMessage);
  
  float interval = 0.5f;
  CCFiniteTimeAction* flashSequence = CCSequence::actions(
                                                          CCFadeIn::actionWithDuration(interval),
                                                          CCFadeOut::actionWithDuration(interval),
                                                          0
                                                          );
  
  CCRepeatForever* flashRepeat = CCRepeatForever::actionWithAction(static_cast<CCActionInterval*>(flashSequence));
  continueMessage->runAction(flashRepeat);
  
  CCTouchDispatcher::sharedDispatcher()->addTargetedDelegate(this, 0, true);
}

bool GrapplingHookRewardSceneView::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent) {
  CCTouchDispatcher::sharedDispatcher()->removeDelegate(this);
  this->unscheduleUpdate();
  controller_->continueToGame();
  return true;
}
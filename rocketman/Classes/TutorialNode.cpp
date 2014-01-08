#include "TutorialNode.h"

#include "cocos2d.h"
USING_NS_CC;

#include "Common.h"
#include "CClabelBNFont.h"

static const int TAG_TUTORIAL = 100;
static const int TAG_TUTORIAL_CONTINUE = 101;

static const float FADE_TIME = 0.1f;

TutorialNode::~TutorialNode() {
  CCTouchDispatcher::sharedDispatcher()->removeDelegate(this);
}

TutorialNode* TutorialNode::node(const Array<String>& tutorials) {
  TutorialNode* node = new TutorialNode(tutorials);
  node->init();
  node->autorelease();
  return node;
}

TutorialNode::TutorialNode(const Array<String>& tutorials) 
  : tutorialIndex_(0), 
  tutorials_(tutorials) { }

bool TutorialNode::init() {
  {
    CCTouchDispatcher::sharedDispatcher()->addTargetedDelegate(this, 0, true);
  }
  
  {
    CCSprite* glassPanel = CCSprite::sprite();
    glassPanel->setOpacity(0);
    CCSize screenSize = CCDirector::sharedDirector()->getWinSize();
    glassPanel->setTextureRect(CCRectMake(0, 0, screenSize.width, screenSize.height));
    addChild(glassPanel);
  }
  
  {
    CCSprite* background = CCSprite::spriteWithSpriteFrameName("tutorial_background.png");
    addChild(background);
  }
    
  {
    showTutorial();
  }
    
  return true;
}

void TutorialNode::removeNode(void *obj) {
  CCNode* node = (CCNode*)obj;
  node->removeFromParentAndCleanup(true);
}

void TutorialNode::nextTutorial() {
  {
    CCNode* oldTextLabel = getChildByTag(TAG_TUTORIAL);
    CCFadeOut* textMoveOutEase = CCFadeOut::actionWithDuration(FADE_TIME);
    CCCallFuncND* removeText = CCCallFuncND::actionWithTarget(this, callfuncND_selector(TutorialNode::removeNode), oldTextLabel);
    CCFiniteTimeAction* textSequence = CCSequence::actions(textMoveOutEase, removeText, 0);
    oldTextLabel->runAction(textSequence);
  }
  
  {
    CCNode* oldContinueLabel = getChildByTag(TAG_TUTORIAL_CONTINUE);
    CCFadeOut* tapMoveOutEase = CCFadeOut::actionWithDuration(FADE_TIME);
    CCCallFunc* nextText = CCCallFunc::actionWithTarget(this, callfunc_selector(TutorialNode::showTutorial));
    CCCallFuncND* removeTap = CCCallFuncND::actionWithTarget(this, callfuncND_selector(TutorialNode::removeNode), oldContinueLabel);
    CCFiniteTimeAction* tapSequence = CCSequence::actions(tapMoveOutEase, removeTap, nextText, 0);
    oldContinueLabel->runAction(tapSequence);
  }
}

void TutorialNode::showTutorial() {
  {
    CCLabelBNFont* textLabel = CCLabelBNFont::labelWithString(tutorials_.objectAtIndex(tutorialIndex_).c_str(), "soupofjustice_26_white.fnt");
    textLabel->setPosition(ccp(0, 10));
    textLabel->setOpacity(0);
    addChild(textLabel, 0, TAG_TUTORIAL);  
    CCFadeIn* textFadeIn = CCFadeIn::actionWithDuration(FADE_TIME);
    textLabel->runAction(textFadeIn);
  }
  
  {
    CCLabelBNFont* continueLabel = CCLabelBNFont::labelWithString("(tap to continue)", "soupofjustice_14_white.fnt");
    continueLabel->setPosition(ccp(0, -31));
    continueLabel->setOpacity(0);
    addChild(continueLabel, continueLabel->getZOrder(), TAG_TUTORIAL_CONTINUE);
    CCFadeIn* fadeIn = CCFadeIn::actionWithDuration(FADE_TIME);
    continueLabel->runAction(fadeIn);
  }
}

bool TutorialNode::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent) { 
  return true;
}

void TutorialNode::ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent) {
  if (++tutorialIndex_ == tutorials_.count()) {
    CCFadeOut* fadeOutEase = CCFadeOut::actionWithDuration(FADE_TIME);
    CCCallFuncND* removeAction = CCCallFuncND::actionWithTarget(this, callfuncND_selector(TutorialNode::removeNode), this);
    CCFiniteTimeAction* textSequence = CCSequence::actions(fadeOutEase, removeAction, 0);
    this->runAction(textSequence);
    return;
  }
  nextTutorial();
  return;
}
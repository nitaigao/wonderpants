#include "GameView.h"

#include "Common.h"

#include "AnimationCompleteHandler.h"
#include "CCCancellableCallfuncND.h"

#include "Component.h"

#include "ShakeAction.h"
#include "CClabelBNFont.h"
#include "CircleNode.h"
#include "FollowAction.h"
#include "RopeNode.h"
#include "TutorialNode.h"
#include "SpatialDecorator.h"

#include "cocos2d.h"
USING_NS_CC;

#include <typeinfo>

static int TAG_BACKGROUND = 100;
static int TAG_FADE = 200;
static int TAG_ANIMATION = 300;

static const int Z_LEVEL_END_BACKGROUND = 2;
static const int Z_SWING_CIRCLE = 4;
static const int Z_SWING = 30;
static const int Z_TUTORIAL = 999;

GameView* GameView::node() {
  GameView* view = new GameView();
  view->init();
  view->autorelease();
  return view;
}

void GameView::init() {
  this->scheduleUpdate();
}

void GameView::update(ccTime dt) {
  if (m_pChildren) {
    ccArray *arrayData = m_pChildren->data;
    for(unsigned int i = 0 ; i < arrayData->num; i++) {
      CCNode* node = static_cast<CCNode*>(arrayData->arr[i]);
      if (!node->getUserData()) continue;

      // particles are updated by follow actions
      if (typeid(*node) == typeid(CCParticleSystemQuad)) continue;

      Component* component = (Component*)node->getUserData();
      SpatialDecorator spatial(component);
      
      CCPoint position = ccp(spatial.x(), spatial.y());
      node->setPosition(position);      
      
      float rotation = spatial.rotation();
      node->setRotation(rotation);
    }
  }
}

void GameView::addSprite(const String& path, int x, int y, int z, float rotation, int label, Component* spatial, bool isVisible) {
  CCSpriteFrame* frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(path.c_str());
  CCSprite* sprite = 0;
  if (frame) {
    sprite = CCSprite::spriteWithSpriteFrame(frame);
  } else {
    sprite = CCSprite::spriteWithFile(path.c_str());
  }
  sprite->setIsVisible(isVisible);
  sprite->setPosition(ccp(x, y));
  sprite->setRotation(rotation);
  sprite->setTag(label);
  sprite->setUserData(spatial);
  addChild(sprite, z);
}

void GameView::removeSprite(int label) {
  CCArray* nodes = getChildrenByTag(label);
  for (int i = 0; i < nodes->count(); i++) {
    CCNode* node = static_cast<CCNode*>(nodes->objectAtIndex(i));
    if (typeid(*node) != typeid(CCSprite)) continue;
    removeChild(node, true);
  }
}

void GameView::playAnimation(const String& animationName, int label, bool repeats, bool restoreLastFrame, AnimationCompleteHandler* callback) {
  CCArray* nodes = getChildrenByTag(label);
  for (int i = 0; i < nodes->count(); i++) {
    CCNode* node = static_cast<CCNode*>(nodes->objectAtIndex(i));
    if (typeid(*node) != typeid(CCSprite)) continue;
    node->stopAllActions();

    CCArray* actions = CCArray::array();
    
    CCAnimation* animation = CCAnimationCache::sharedAnimationCache()->animationByName(animationName.c_str());
    CCAnimate* animate = CCAnimate::actionWithAnimation(animation, restoreLastFrame);
    animate->setTag(TAG_ANIMATION);
    actions->addObject(animate);

    AnimationCompleteHandler* handler = callback->clone();
    CCCancellableCallfuncND* completeCallback = CCCancellableCallfuncND::actionWithHandler(handler);
    actions->addObject(completeCallback);
    
    CCFiniteTimeAction* sequence = CCSequence::actionsWithArray(actions);
    
    CCAction* actionSequence = repeats ? CCRepeatForever::actionWithAction(static_cast<CCActionInterval*>(sequence)) : sequence;
    node->runAction(actionSequence);    
  } 
  SAFE_DELETE(callback);
}

void GameView::panSceneY(int pixels) {
  CCMoveBy* move = CCMoveBy::actionWithDuration(0.4, ccp(0, pixels));
  CCEaseSineOut* moveEase = CCEaseSineOut::actionWithAction(move);
  runAction(moveEase);
}

void GameView::shakeCamera() {
  ShakeAction* shake = ShakeAction::action(0.2f, 1.5f);
  runAction(shake);
}

void GameView::addParticle(const String& data, int x, int y, int z, int offsetX, int offsetY, int label, Component* spatial) {
  CCParticleSystemQuad* particleSystem = CCParticleSystemQuad::particleWithFile(data.c_str());
  particleSystem->setPosition(ccpAdd(ccp(x, y), ccp(offsetX, offsetY)));
  particleSystem->stopSystem();
  particleSystem->setTag(label);
  particleSystem->setName(data.replace(".plist", "").c_str());
  particleSystem->setUserData(spatial);

  CCArray* parents = getChildrenByTag(label);
  for (int i = 0; i < parents->count(); i++) {
    CCSprite* parent = static_cast<CCSprite*>(parents->objectAtIndex(i));
    if (typeid(*parent) != typeid(CCSprite)) continue;    
    FollowAction* follow = FollowAction::actionWithTarget(parent, ccp(offsetX, offsetY));
    particleSystem->runAction(follow);    
  }

  addChild(particleSystem, z);
}

void GameView::emitParticle(int x, int y, const String& name, int label) {
  CCArray* particles = getChildrenByTag(label);  
  for (int i = 0; i < particles->count(); i++) {
    CCParticleSystemQuad* particle = static_cast<CCParticleSystemQuad*>(particles->objectAtIndex(i));
    if (typeid(*particle) != typeid(CCParticleSystemQuad)) continue;    
    if (String(particle->getName()) == name) {
      particle->resetSystem();
    }
  }
}

void GameView::stopParticle(const String& name, int label) {
  CCArray* particles = getChildrenByTag(label);  
  for (int i = 0; i < particles->count(); i++) {
    CCParticleSystemQuad* particle = static_cast<CCParticleSystemQuad*>(particles->objectAtIndex(i));
    if (typeid(*particle) != typeid(CCParticleSystemQuad)) continue;    
    if (String(particle->getName()) == name) {
      particle->stopSystem();
    }
  }  
}

void GameView::fadeInSprite(int label, float duration) {
  CCArray* nodes = getChildrenByTag(label);
  for (int i = 0; i < nodes->count(); i++) {
    CCNode* node = static_cast<CCNode*>(nodes->objectAtIndex(i));
    if (typeid(*node) != typeid(CCSprite)) continue;
    node->stopActionByTag(TAG_FADE);
    CCFadeIn* fade = CCFadeIn::actionWithDuration(duration);
    fade->setTag(TAG_FADE);
    node->runAction(fade);
  }
}

void GameView::fadeOutSprite(int label, float duration) {
  CCArray* nodes = getChildrenByTag(label);
  for (int i = 0; i < nodes->count(); i++) {
    CCNode* node = static_cast<CCNode*>(nodes->objectAtIndex(i));
    if (typeid(*node) != typeid(CCSprite)) continue;
    node->stopActionByTag(TAG_FADE);
    CCFadeOut* fade = CCFadeOut::actionWithDuration(duration);
    fade->setTag(TAG_FADE);
    node->runAction(fade);
  }  
}

void GameView::addFloatingLabel(int x, int y, int score) {
  String scoreString = String::withFormat("%i", score);
  CCLabelBNFont* scoreLabel = CCLabelBNFont::labelWithString(scoreString.c_str(), "soupofjustice_24_red.fnt");
  scoreLabel->setPosition(ccp(x, y));
  addChild(scoreLabel, 200);

  float time = 1.5f;
  
  CCFadeOut* fadeOut = CCFadeOut::actionWithDuration(time);
  scoreLabel->runAction(fadeOut);
  
  CCMoveBy* moveBy = CCMoveBy::actionWithDuration(time, ccp(0, 30));
  scoreLabel->runAction(moveBy);
}

void GameView::addCircle(int x, int y, float radius, int label) {
  CircleNode* node = CircleNode::node(radius);
  node->setColor(ccWHITE);
  node->setOpacity(255 * 0.3);
  node->setPosition(ccp(x, y));
  addChild(node, Z_SWING_CIRCLE, label);
}

void GameView::fadeInCircle(int label) {
  CCArray* nodes = getChildrenByTag(label);
  for (int i = 0; i < nodes->count(); i++) {
    CCNode* node = static_cast<CCNode*>(nodes->objectAtIndex(i));
    if (typeid(*node) != typeid(CircleNode)) continue;
    CCFadeTo* fadeIn = CCFadeTo::actionWithDuration(0.2, (255 * 0.8));
    node->runAction(fadeIn);
  }    
}

void GameView::fadeOutCircle(int label) {
  CCArray* nodes = getChildrenByTag(label);
  for (int i = 0; i < nodes->count(); i++) {
    CCNode* node = static_cast<CCNode*>(nodes->objectAtIndex(i));
    if (typeid(*node) != typeid(CircleNode)) continue;
    CCFadeTo* fadeIn = CCFadeTo::actionWithDuration(0.2, (255 * 0.3));
    node->runAction(fadeIn);
  }  
}

void GameView::fadeScene(const String& backgroundName) {
  {
    CCSize screenSize = CCDirector::sharedDirector()->getWinSize();
    CCSprite* background = CCSprite::spriteWithSpriteFrameName(backgroundName.c_str());
    background->setTag(TAG_BACKGROUND);
    background->setOpacity(0);
    background->setPosition(ccp(screenSize.width/2, screenSize.height/2));
    addChild(background, Z_LEVEL_END_BACKGROUND);
    CCFadeIn* fade = CCFadeIn::actionWithDuration(0.9f);
    background->runAction(fade);
  }
  
  {
    for (int i = 0; i < m_pChildren->count(); i++) {
      CCNode* node = static_cast<CCNode*>(m_pChildren->objectAtIndex(i));
      if (node->getTag() == TAG_BACKGROUND) continue;
      
      if (typeid(*node) == typeid(CCSprite) || typeid(*node) == typeid(CircleNode)) {
        CCTintTo* tint = CCTintTo::actionWithDuration(0.7f, ccBLACK.r, ccBLACK.g, ccBLACK.b);
        node->runAction(tint);
      }
    }
  }
}

void GameView::createRope(int from, int to) {
  CCNode* fromNode = getChildByTag(from);
  CCNode* toNode = getChildByTag(to);
  RopeNode* rope = RopeNode::node(fromNode, toNode);
  addChild(rope, Z_SWING);
  ropes_.addObject(rope);
}

void GameView::deleteRope() {
  for (CCNode* node : ropes_) {
    removeChild(node, true);
  }
  ropes_.removeAllObjects();
}

void GameView::addTutorials(const Array<String>& tutorials) {
  TutorialNode* tutorialNode = TutorialNode::node(tutorials);
  CCSize screenSize = CCDirector::sharedDirector()->getWinSize();
  tutorialNode->setPosition(ccp(screenSize.width/2, 150));
  addChild(tutorialNode, Z_TUTORIAL);
}

void GameView::flipX(int label) {
  CCArray* nodes = getChildrenByTag(label);  
  for (int i = 0; i < nodes->count(); i++) {
    CCNode* node = static_cast<CCNode*>(nodes->objectAtIndex(i));
    if (typeid(*node) == typeid(CCSprite)) {
      node->setScaleX(-node->getScaleX());
    }
  }
}

void GameView::setVisible(bool isVisible, int label) {
  CCArray* nodes = getChildrenByTag(label);  
  for (int i = 0; i < nodes->count(); i++) {
    CCNode* node = static_cast<CCNode*>(nodes->objectAtIndex(i));
    if (typeid(*node) == typeid(CCSprite)) {
      node->setIsVisible(isVisible);
    }
  }  
}
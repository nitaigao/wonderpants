#include "TransitionScene.h"

#include "SoundSystem.h"

USING_NS_CC;

static const float SWAP_DELAY = 0.1f;
static const int TAG_BACKGROUND = 101;
static const int TAG_SPRITESHEET = 102;

bool TransitionScene::init() {
  CCScene::init();
  
  CCMutableArray<CCSpriteFrame*> animationFrames;
  CCSpriteFrame* frame1 = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("transition_sunburst_01.png");
  animationFrames.addObject(frame1);
  CCSpriteFrame* frame2 = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("transition_sunburst_02.png");
  animationFrames.addObject(frame2);
  
  CCAnimation* animation = CCAnimation::animationWithFrames(&animationFrames, SWAP_DELAY);
  CCAnimationCache::sharedAnimationCache()->addAnimation(animation, "burst_swap");
  
  CCSize screenSize = CCDirector::sharedDirector()->getWinSize();
  
  CCSprite* background = CCSprite::spriteWithSpriteFrameName("transition_sunburst_01.png");
  background->setPosition(ccp(screenSize.width/2, screenSize.height/2));
  addChild(background, 0, TAG_BACKGROUND);

  return true;
}

void TransitionScene::onEnterTransitionDidFinish() {
  CCScene::onEnterTransitionDidFinish();

  SoundSystem::sharedSoundSystem()->muteMusic();
  SoundSystem::sharedSoundSystem()->playEffect("scene_transition");
  
  CCAnimation* animation = CCAnimationCache::sharedAnimationCache()->animationByName("burst_swap");
  
  CCNode* background = getChildByTag(TAG_BACKGROUND);
  background->runAction(CCRepeatForever::actionWithAction(CCAnimate::actionWithAnimation(animation)));
  
  CCSize screenSize = CCDirector::sharedDirector()->getWinSize();
  
  CCSprite* catLogo = CCSprite::spriteWithSpriteFrameName("transition_cat.png");
  catLogo->setPosition(ccp(screenSize.width / 2, screenSize.height / 2));
  catLogo->setScale(0);
  catLogo->setAnchorPoint(ccp(0.5, 0.5));
  addChild(catLogo);
  
  CCFiniteTimeAction* sequence = CCSequence::actions
  (
   CCScaleTo::actionWithDuration(0.5, 1.2),
   CCScaleTo::actionWithDuration(0.5, 0),
   CCCallFunc::actionWithTarget(this, callfunc_selector(TransitionScene::finishUp)),
   NULL
  );
  
  catLogo->runAction(sequence);
}

void TransitionScene::finishUp() {
  SoundSystem::sharedSoundSystem()->unMuteMusic();
  finish();
}
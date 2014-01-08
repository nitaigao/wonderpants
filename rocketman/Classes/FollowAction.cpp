#include "FollowAction.h"

USING_NS_CC;

FollowAction::~FollowAction() {
  followedNode_->release();
}

FollowAction* FollowAction::actionWithTarget(cocos2d::CCNode* target, cocos2d::CCPoint offset) {
  FollowAction* action = new FollowAction(target, offset);
  action->autorelease();
  return action;
}

FollowAction::FollowAction(CCNode* target, CCPoint offset) 
  : followedNode_(target)
  , offset_(offset) {
    followedNode_->retain();
}

void FollowAction::step(cocos2d::ccTime dt) {
  m_pTarget->setPosition(followedNode_->getPosition());
}

bool FollowAction::isDone() {
  return !followedNode_->getIsRunning();
}

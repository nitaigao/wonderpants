#include "ShakeAction.h"

ShakeAction* ShakeAction::action(float duration, float radius) {
  ShakeAction* action = new ShakeAction();
  action->autorelease();
  action->init(duration, radius);
  return action;
}

void ShakeAction::init(float duration, float radius) {
  m_fDuration = duration;
  radius_ = radius;  
  time_ = 0;
}

void ShakeAction::startWithTarget(CCNode* target) {
  CCFiniteTimeAction::startWithTarget(target);
  originalPosition = target->getPosition();
}

void ShakeAction::step(ccTime dt) {
  time_ += dt;
  float angleX = (arc4random() % 10 ) + 1;
  float angleY = (arc4random() % 10 ) + 1;
  
  float rotatedX = cosf(angleX) - sinf(angleY);
  float rotatedY = sinf(angleX) + cosf(angleY);
  
  rotatedX *= radius_;
  rotatedY *= radius_;
  
  m_pTarget->setPosition(ccp(originalPosition.x + rotatedX, originalPosition.y + rotatedY)); 
}

void ShakeAction::stop() {
  CCFiniteTimeAction::stop();
}

bool ShakeAction::isDone() {
  return time_ >= m_fDuration;
}
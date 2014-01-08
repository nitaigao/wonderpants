#include "ScoreCountUpAction.h"

#include "Common.h"
#include "SoundSystem.h"
#include "CClabelBNFont.h"

ScoreCountUpAction::ScoreCountUpAction(int count, CCLabelBNFont* target, float duration, float blipInterval)
  : count_(count) 
  , target_(target)
  , duration_(duration)
  , blipInterval_(blipInterval)
  , currentCount_(0)
  , blipCount_(0) { }

ScoreCountUpAction* ScoreCountUpAction::actionWithCount(int count, CCLabelBNFont* target, float duration, float blipInterval) {
  ScoreCountUpAction* action = new ScoreCountUpAction(count, target, duration, blipInterval);
  action->initWithDuration(duration);
  action->autorelease();
  return action;
}

void ScoreCountUpAction::update(cocos2d::ccTime time) {
  currentCount_ = count_ * time;
  
  int newBlipCount = currentCount_ / blipInterval_;
  
  if (newBlipCount > blipCount_) {
    SoundSystem::sharedSoundSystem()->playEffect("coin_count_blip");
    blipCount_ = newBlipCount;
  }
  
  target_->setString(String::withFormat("Score: %d", (int)currentCount_).c_str()); 
}

void ScoreCountUpAction::stop() {
  CCActionInterval::stop();
  SoundSystem::sharedSoundSystem()->playEffect("coin_award_end");
}
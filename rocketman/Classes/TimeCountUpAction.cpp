#include "TimeCountUpAction.h"

#include "SoundSystem.h"
#include "Common.h"
#include "CClabelBNFont.h"

TimeCountUpAction::TimeCountUpAction(int count, CCLabelBNFont* target, float duration, float blipInterval)
  : count_(count) 
  , target_(target)
  , duration_(duration)
  , blipInterval_(blipInterval)
  , currentCount_(0)
  , blipCount_(0) { }

TimeCountUpAction* TimeCountUpAction::actionWithCount(int count, CCLabelBNFont* target, float duration, float blipInterval) {
  TimeCountUpAction* action = new TimeCountUpAction(count, target, duration, blipInterval);
  action->initWithDuration(duration);
  action->autorelease();
  return action;
}

void TimeCountUpAction::update(cocos2d::ccTime time) {
  currentCount_ = count_ * time;
  
  int newBlipCount = currentCount_ / blipInterval_;
  
  if (newBlipCount > blipCount_) {
    SoundSystem::sharedSoundSystem()->playEffect("coin_count_blip");
    blipCount_ = newBlipCount;
  }
  
  int seconds = (int)currentCount_ % 60; 
  int minutes = (int)(currentCount_ / 60.0f) % 60; 
  target_->setString(String::withFormat("Time: %02d:%02d", minutes, seconds).c_str()); 
}

#include "SpriteSheetLoadTask.h"

#include "cocos2d.h"
USING_NS_CC;

SpriteSheetLoadTask::SpriteSheetLoadTask(const String& spriteSheet) : spriteSheet_(spriteSheet) {
  
}

void SpriteSheetLoadTask::execute() {
  CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(spriteSheet_.c_str());
}

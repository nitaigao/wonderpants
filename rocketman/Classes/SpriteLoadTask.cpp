#include "SpriteLoadTask.h"

#include "cocos2d.h"
USING_NS_CC;

SpriteLoadTask::SpriteLoadTask(const String& spriteFile) : spriteFile_(spriteFile) {
  
}

void SpriteLoadTask::execute() {
//  CCTextureCache::sharedTextureCache()->addImage(spriteFile_.c_str());
}

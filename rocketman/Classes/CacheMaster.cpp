#include "CacheMaster.h"

#include "ResourceCache.h"

#include "cocos2d.h"
USING_NS_CC;

#include "SimpleAudioEngine.h"
using namespace CocosDenshion;

#include "LevelCache.h"

void CacheMaster::purgeTemporaryCaches() {
  CCDirector::sharedDirector()->purgeCachedData();
  ResourceCache::purgeCache();
}

void CacheMaster::purgeAllCaches() {
  LevelCache::purgeSharedLevelCache();
  CCSpriteFrameCache::purgeSharedSpriteFrameCache();
  CCAnimationCache::purgeSharedAnimationCache();
  CCTextureCache::purgeSharedTextureCache();  
  ResourceCache::purgeCache();
}

#include "BackgroundCache.h"

#include "ChapterData.h"

#include "Common.h"

#include "cocos2d.h"
USING_NS_CC;

void BackgroundCache::cacheBackgroundForNextLevel(int chapter, int level) {
  Array<String> prefixes = Array<String>::fromObjects("country", "city", "jungle");
  
  int thisLevel = level + 1;
  int levelToCache = thisLevel + 1; // zero indexed level + the next level
  int levelToRelease = thisLevel - 1; // zero indexed level - this level

  int levelCount = ChapterData::forChapter(chapter).levels();
  if (thisLevel < levelCount) {
    String newSilhouette = String::withFormat("%s_silhouette_%0.2d.png", prefixes.objectAtIndex(chapter).c_str(), levelToCache);
    CCTextureCache::sharedTextureCache()->addImage(newSilhouette.c_str());
//    CCTextureCache::sharedTextureCache()->addImageAsync(newSilhouette.c_str(), 0, 0);
  }
  
  if (level > 0) {
    String oldSilhouette = String::withFormat("%s_silhouette_%0.2d.png", prefixes.objectAtIndex(chapter).c_str(), levelToRelease);
    CCTextureCache::sharedTextureCache()->removeTextureForKey(oldSilhouette.c_str());
  }
}
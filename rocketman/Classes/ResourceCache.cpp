#include "ResourceCache.h"

#include "CCFileUtils.h"
USING_NS_CC;

#include "Common.h"

static ResourceCache* _sharedCache = 0;

ResourceCache::~ResourceCache() {
  for (auto cacheItem : binaryCache_) {
    SAFE_DELETE(cacheItem.second);
  }
}

ResourceCache* ResourceCache::sharedCache() {
  if (!_sharedCache) {
    _sharedCache = new ResourceCache();
  }
  return _sharedCache;
}

void ResourceCache::purgeCache() {
  SAFE_DELETE(_sharedCache);
}

String ResourceCache::loadString(const char *path) {
  if (stringCache_.find(path) == stringCache_.end()) {
    const char* fullPath = CCFileUtils::fullPathFromRelativePath(path);
    stringCache_[path] = String::fromFile(fullPath);        
  }
  return stringCache_[path];
}

CCFileData* ResourceCache::loadBinary(const char *path) {
  if (binaryCache_.find(path) == binaryCache_.end()) {
    const char* fullPath = CCFileUtils::fullPathFromRelativePath(path);
    binaryCache_[path] = new CCFileData(fullPath, "rb");
  }
  return binaryCache_[path];
}
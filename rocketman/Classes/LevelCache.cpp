#include "LevelCache.h"

#include "Common.h"

#include "Level.h"
#include "json.h"
#include "CCFileUtils.h"
#include "LevelsParser.h"
#include "ChapterData.h"
#include "GameConfig.h"

#include "GameConfig.h"
#include "ResourceCache.h"

#include "Component.h"
#include "Entity.h"

static LevelCache* sharedCache_ = 0;

LevelCache* LevelCache::sharedCache() {
  if (!sharedCache_) {
    sharedCache_ = new LevelCache();
  }
  return sharedCache_;
}

void LevelCache::purgeSharedLevelCache() {
  SAFE_DELETE(sharedCache_);
}

LevelCache::~LevelCache() {
  for (Level* level : masterLevelCache) {
    SAFE_DELETE(level);
  }
}

void LevelCache::addChapterData(const String& levelsFilePath) {
  String fullPath = cocos2d::CCFileUtils::fullPathFromRelativePath(levelsFilePath.c_str());
  LevelsParser parser;
  
  Level* level = Level::level();
  parser.levelsFromFile(fullPath, level);
  masterLevelCache.addObject(level);  
}

Entity* LevelCache::loadPrefab(const String& path) {
  String json = ResourceCache::sharedCache()->loadString(path.c_str());
  
  Json::Value root;
  Json::Reader reader;
  reader.parse(json.str(), root);
  
  Entity* entity = new Entity();
  LevelsParser().parseEntity(root, entity);
  return entity;
}

Level* LevelCache::level(int levelIndex) {  
  Level* level = masterLevelCache.objectAtIndex(levelIndex);
  return level->clone();
}

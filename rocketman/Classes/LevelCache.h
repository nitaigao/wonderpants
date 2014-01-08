#ifndef LevelCache_H_
#define LevelCache_H_

#include "Common.h"
#include "LevelsParser.h"

class Level;

class LevelCache {
  
private:
  
  ~LevelCache();
  
public:
  
  static LevelCache* sharedCache();
  
  static void purgeSharedLevelCache();
  
public:
  
  void addChapterData(const String& levelsFilePath);
  
  Level* level(int level);
  
public:
  
  Level* level(int chapter, int level);
  
  Entity* loadPrefab(const String& path);
  
private:
  
  int findLevelIndex(int level, int chapter);
  
private:
  
  Array<Level*> masterLevelCache;  
  
};

#endif

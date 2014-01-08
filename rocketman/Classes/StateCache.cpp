#include "StateCache.h"

#include "Common.h"
#include "Platform.h"
#include "LuaState.h"

#include <dirent.h>

static StateCache* _sharedCache = 0;

StateCache* StateCache::sharedCache() {
  if (!_sharedCache) {
    _sharedCache = new StateCache();
    _sharedCache->init();
  }
  return _sharedCache;
}

void StateCache::init() {
  DIR *dirp;
  struct dirent *entry;
  if((dirp = opendir(Platform::currentPlatform()->appPath().c_str())))
  {
    while((entry = readdir(dirp))) {
      if (String(entry->d_name).contains("luac")) {
        //TODO: implement the cache
      }
    }
    closedir(dirp);
  }  
}

LuaState* StateCache::stateForPath(const String& path, Level* level) {
  return 0;
//  return LuaState::stateWithScript(path, level);
}
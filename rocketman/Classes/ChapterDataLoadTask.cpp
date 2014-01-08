#include "ChapterDataLoadTask.h"

#include "LevelCache.h"

ChapterDataLoadTask::ChapterDataLoadTask(const String& dataFile) 
  : dataFile_(dataFile) {
  
}

void ChapterDataLoadTask::execute() {
  LevelCache::sharedCache()->addChapterData(dataFile_);
}
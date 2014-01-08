#include "NextChapterStrategy.h"

#include "ScreenManager.h"

NextChapterStrategy::NextChapterStrategy(int chapter, int level) : chapter_(chapter), level_(level) {
  
}

void NextChapterStrategy::execute() {
  ScreenManager::loadAndUnlockChapterScreen(chapter_ + 1);
}
#include "NextLevelStrategy.h"

#include "ScreenManager.h"

NextLevelStrategy::NextLevelStrategy(int chapter, int level) : chapter_(chapter), level_(level) {
  
}

void NextLevelStrategy::execute() {
  ScreenManager::transitionToGameScreen(chapter_, level_);
}
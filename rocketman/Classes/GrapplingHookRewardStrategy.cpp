#include "GrapplingHookRewardStrategy.h"

#include "ScreenManager.h"

GrapplingHookRewardStrategy::GrapplingHookRewardStrategy(int chapter, int level) : chapter_(chapter), level_(level) {
  
}

void GrapplingHookRewardStrategy::execute() {
  ScreenManager::activateGrapplingHookRewardScreen(chapter_, level_);
}
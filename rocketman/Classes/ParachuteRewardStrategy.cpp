#include "ParachuteRewardStrategy.h"

#include "ScreenManager.h"

ParachuteRewardStrategy::ParachuteRewardStrategy(int chapter, int level) : chapter_(chapter), level_(level) {
  
}

void ParachuteRewardStrategy::execute() {
  ScreenManager::activateParachuteRewardScreen(chapter_, level_);
}
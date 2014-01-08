#include "EndGameStrategy.h"

#include "ScreenManager.h"

EndGameStrategy::EndGameStrategy(int chapter) : chapter_(chapter) {
  
}

void EndGameStrategy::execute() {
  ScreenManager::loadAndDisplayEndGameScreen(chapter_);
}
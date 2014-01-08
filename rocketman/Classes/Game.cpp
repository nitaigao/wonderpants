#include "Game.h"

#include "ScreenManager.h"
#include "SoundSystem.h"
#include "GameConfig.h"
#include "SaveGame.h"
#include "ResourceCache.h"
#include "LevelCache.h"

#include "Entity.h"

#include "PerformanceTimer.h"

void Game::run() {
  SoundSystem::sharedSoundSystem()->init();
  SaveGame::sharedSaveData()->cacheSaveData();
  ScreenManager::loadAndDisplayTitleScreen();  
}
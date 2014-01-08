#include "DefaultStatsStore.h"

#include "Common.h"
#include "SaveState.h"

void DefaultStatsStore::startSession() {
  Log("Stats: starting session");
}

void DefaultStatsStore::winLevel(const SaveState& saveState) {
  Log("Stats: level win chapter:%d level:%d attempts:%d coins:%d", saveState.chapter(), saveState.level(), saveState.attempts(), saveState.coins());
}

void DefaultStatsStore::loseLevel(int level, int chapter) {
  Log("Stats: level lose chapter:%d level:%d", chapter, level);
}
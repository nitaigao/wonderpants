#include "SaveState.h"

#include "PlayerState.h"

SaveState::SaveState(int chapterIndex, int levelIndex, int coins, int bonus, int attempts, long time) 
  : chapterIndex_(chapterIndex)
  , levelIndex_(levelIndex)
  , coins_(coins)
  , bonus_(bonus)
  , attempts_(attempts) 
  , time_(time) { };


int SaveState::level() const {
  return levelIndex_ + 1;
}

int SaveState::chapter() const {
  return chapterIndex_ + 1;
}

int SaveState::attempts() const {
  return attempts_;
}

int SaveState::coins() const {
  return coins_;
}

int SaveState::score() const {
  int collectableScore = coins() * 1000;
  int styleScore = bonus();
  int timeScore = !time_ ? 0 : 2000.0f / time_;
  return collectableScore + timeScore + styleScore;
}

int SaveState::bonus() const {
  return bonus_;
}

int SaveState::chapterIndex() const {
  return chapterIndex_;
}

int SaveState::levelIndex() const {
  return levelIndex_;
}

long SaveState::levelTime() const {
  return time_;
}
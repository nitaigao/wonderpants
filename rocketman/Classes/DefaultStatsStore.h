#ifndef DEFAULTSTATSSTORE_H
#define DEFAULTSTATSSTORE_H

#include "StatsDataStore.h"

class DefaultStatsStore : public StatsDataStore {
  
public:
  
  void startSession();
  
  void winLevel(const SaveState& saveState);
  
  void loseLevel(int level, int chapter);
  
};

#endif

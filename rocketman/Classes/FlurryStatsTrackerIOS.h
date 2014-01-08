#ifndef FlurryStatsTrackerIOS_H_
#define FlurryStatsTrackerIOS_H_

#include "StatsDataStore.h"

class FlurryStatsTrackerIOS : public StatsDataStore {
  
public:
  
  void startSession();
  
  void winLevel(const SaveState& saveState);
  
  void loseLevel(int level, int chapter);
  
};

#endif

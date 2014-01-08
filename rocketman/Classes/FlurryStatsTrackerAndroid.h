#ifndef FlurryStatsTrackerAndroid_H_
#define FlurryStatsTrackerAndroid_H_

#include "StatsDataStore.h"

class FlurryStatsTrackerAndroid : public StatsDataStore {
  
public:
  
  void startSession();
  
  void winLevel(const SaveState& saveState);
  
  void loseLevel(int level, int chapter);
  
};

#endif

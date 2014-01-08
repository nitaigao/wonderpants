#ifndef STATSTRACKER_H
#define STATSTRACKER_H

class SaveState;
class StatsDataStore;

class StatsTracker {
  
public:
  
  StatsTracker();
  
  ~StatsTracker();
  
public:
  
  void startSession();
  
  void winLevel(const SaveState& saveState);
  
  void loseLevel(int level, int chapter);
  
private:
  
  StatsDataStore* dataStore_;
  
};

#endif

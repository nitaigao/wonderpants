#ifndef STATSDATASTORE_H
#define STATSDATASTORE_H

class SaveState;

class StatsDataStore {
  
public:
  
  virtual void startSession() = 0;
  
  virtual void winLevel(const SaveState&) = 0;
  
  virtual void loseLevel(int level, int chapter) = 0;
  
};

#endif

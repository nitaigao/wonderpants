#ifndef NextLevelStrategy_H_
#define NextLevelStrategy_H_

#include "EndOfLevelStrategy.h"

class NextLevelStrategy : public EndOfLevelStrategy {
  
public:
  
  NextLevelStrategy(int chapter, int level);
  
  void execute();
  
private:
  
  int chapter_;
  int level_;
  
};

#endif

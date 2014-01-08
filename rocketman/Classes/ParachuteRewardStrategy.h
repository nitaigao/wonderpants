#ifndef ParachuteRewardStrategy_H_
#define ParachuteRewardStrategy_H_

#include "EndOfLevelStrategy.h"

class ParachuteRewardStrategy : public EndOfLevelStrategy {
  
public:
  
  ParachuteRewardStrategy(int chapter, int level);
  
public:
  
  void execute();
  
private:
  
  int chapter_;
  int level_;
  
};

#endif

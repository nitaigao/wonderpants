#ifndef GrapplingHookRewardStrategy_H_
#define GrapplingHookRewardStrategy_H_

#include "EndOfLevelStrategy.h"

class GrapplingHookRewardStrategy : public EndOfLevelStrategy {
  
public:
  
  GrapplingHookRewardStrategy(int chapter, int level);
  
public:
  
  void execute();
  
private:
  
  int chapter_;
  int level_;
  
};

#endif

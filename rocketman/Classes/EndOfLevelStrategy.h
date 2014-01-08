#ifndef EndOfLevelStrategy_H_
#define EndOfLevelStrategy_H_

#include "Common.h"

class EndOfLevelStrategy {
  
public:
  
  static shared_ptr<EndOfLevelStrategy> strategy(int chapter, int level);
  
public:
  
  virtual ~EndOfLevelStrategy() { };
  
public:
  
  virtual void execute() = 0;
  
};

#endif

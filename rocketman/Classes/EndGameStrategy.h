#ifndef EndGameStrategy_H_
#define EndGameStrategy_H_

#include "EndOfLevelStrategy.h"

class EndGameStrategy : public EndOfLevelStrategy {
  
public:
  
  EndGameStrategy(int chapter);
  
  void execute();
  
private:
  
  int chapter_;
    
};

#endif

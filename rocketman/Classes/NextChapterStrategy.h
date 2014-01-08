#ifndef NextChapterStrategy_H_
#define NextChapterStrategy_H_

#include "EndOfLevelStrategy.h"

class NextChapterStrategy : public EndOfLevelStrategy {
  
public:
  
  NextChapterStrategy(int chapter, int level);
  
  void execute();
  
private:
  
  int chapter_;
  int level_;

  
};

#endif

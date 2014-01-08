#include "EndOfLevelStrategy.h"

#include "NextLevelStrategy.h"
#include "NextChapterStrategy.h"
#include "ParachuteRewardStrategy.h"
#include "GrapplingHookRewardStrategy.h"
#include "EndGameStrategy.h"

#include "ChapterData.h"
#include "GameConfig.h"

shared_ptr<EndOfLevelStrategy> EndOfLevelStrategy::strategy(int chapter, int level) {
  
  if (level == 9 && chapter == 0) {
    return shared_ptr<ParachuteRewardStrategy>(new ParachuteRewardStrategy(chapter, level));
  }
  
  if (level == 5 && chapter == 1) {
    return shared_ptr<GrapplingHookRewardStrategy>(new GrapplingHookRewardStrategy(chapter, level));
  }
  
  if (level == 24 && chapter == 2) {
    return shared_ptr<EndGameStrategy>(new EndGameStrategy(chapter));
  }
  
  if (level == ChapterData::chapters().first().levels()) {
    return shared_ptr<EndOfLevelStrategy>(new NextChapterStrategy(chapter, level));
  }
  
  return shared_ptr<EndOfLevelStrategy>(new NextLevelStrategy(chapter, level));
}
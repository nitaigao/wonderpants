#include "GameConfig.h"

String GameConfig::levelsFile() {  
#if defined (LITE_GAME)
  return "levels_demo.json";
#endif
  
#if defined (FULL_GAME)
  return "levels.json";
#endif
  
  return "no-game-specified";
}

String GameConfig::chaptersFile() {
#if defined (LITE_GAME)
  return "chapters_demo.json";
#endif
  
#if defined (FULL_GAME)
  return "chapters.json";
#endif
  
  return "no-game-specified";
}

int GameConfig::levelColumns() {
  return 6;
}

int GameConfig::levelRows() {
  return 4;
}
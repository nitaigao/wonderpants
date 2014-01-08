#ifndef __SCREEN_MANAGER_H
#define __SCREEN_MANAGER_H

class ScreenManager {
  
public:
  
  static void activateTitleScreen();
  
  static void activateOptionsScreen();
  
  static void activateCreditsScreen();
  
  static void activateChaptersScreen(int chapter);
  
  static void activateChaptersScreenUnlockChapter(int chapter);
  
  static void activateChapterIntroScreen(int chapter);
  
  static void activateLevelsScreen(int chapter);
  
  static void activateGameScreen(int chapter, int level);
  
  static void activateParachuteRewardScreen(int chapter, int level);
  
  static void activateGrapplingHookRewardScreen(int chapter, int level);
  
  static void activateEndGameScreen(int chapter);
  
#ifdef CHEATS
  static void activateCheatsScreen();
#endif
  
public:
  
  static void loadAndDisplayTitleScreen();
  
  static void loadAndDisplayGameScreen(int chapter, int level);
  
  static void loadAndChaptersScreen(int chapter);
  
  static void loadAndLevelsScreen(int chapter);
  
  static void loadAndDisplayChapterIntroScreen(int chapter);
  
  static void loadAndUnlockChapterScreen(int chapter);
  
  static void loadAndDisplayEndGameScreen(int chapter);
  
public:
  
  static void transitionToGameScreen(int chapter, int level);
  
public:
  
  static void cutToGameScreen(int chapter, int level);
  
};

#endif

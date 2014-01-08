#include "ScreenManager.h"

#include "cocos2d.h"
USING_NS_CC;

#include "TitleScene.h"
#include "OptionsScene.h"
#include "CreditsScene.h"
#include "ChaptersScene.h"
#include "LevelsScene.h"
#include "GameScene.h"
#include "ChapterIntroScene.h"
#include "EndGameScene.h"

#include "GameLoadingScene.h"
#include "ChaptersLoadingScene.h"
#include "LevelsLoadingScene.h"
#include "BootLoaderScene.h"
#include "ChapterIntroLoadingScene.h"
#include "ChapterUnlockedLoadingScene.h"
#include "ParachuteRewardScene.h"
#include "GrapplingHookRewardScene.h"
#include "EndGameLoadingScene.h"

#include "GameTransitionScene.h"
#include "BackgroundCache.h"

#ifdef CHEATS
#include "CheatsScene.h"
#endif

#include "TestScene.h"

static const float TRANSITION_LENGTH = 0.3f;

void ScreenManager::loadAndDisplayTitleScreen() {
  BootLoaderScene* scene = BootLoaderScene::node();
  CCDirector::sharedDirector()->runWithScene(scene);  
}

void ScreenManager::activateTitleScreen() {
  CCScene* scene = TitleScene::node();
  CCTransitionFade* fade = CCTransitionFade::transitionWithDuration(TRANSITION_LENGTH, scene);
  CCDirector::sharedDirector()->replaceScene(fade);
}

void ScreenManager::activateOptionsScreen() {
  CCScene* scene = OptionsScene::node();
  CCTransitionFade* fade = CCTransitionFade::transitionWithDuration(TRANSITION_LENGTH, scene);
  CCDirector::sharedDirector()->replaceScene(fade);  
}

void ScreenManager::activateCreditsScreen() {
  CCScene* scene = CreditsScene::node();
  CCTransitionFade* fade = CCTransitionFade::transitionWithDuration(TRANSITION_LENGTH, scene);
  CCDirector::sharedDirector()->replaceScene(fade);    
}

void ScreenManager::activateChaptersScreen(int chapter) {
  CCScene* scene = ChaptersScene::nodeWithChapter(chapter);
  CCTransitionFade* fade = CCTransitionFade::transitionWithDuration(TRANSITION_LENGTH, scene);
  CCDirector::sharedDirector()->replaceScene(fade);      
}

void ScreenManager::activateChapterIntroScreen(int chapter) {
  CCScene* scene = ChapterIntroScene::nodeWithChapter(chapter);
  CCTransitionFade* fade = CCTransitionFade::transitionWithDuration(TRANSITION_LENGTH, scene);
  CCDirector::sharedDirector()->replaceScene(fade);      
}

void ScreenManager::activateLevelsScreen(int chapter) {
  CCScene* scene = LevelsScene::nodeWithChapter(chapter);
  CCTransitionFade* fade = CCTransitionFade::transitionWithDuration(TRANSITION_LENGTH, scene);
  CCDirector::sharedDirector()->replaceScene(fade);      
}

void ScreenManager::activateGameScreen(int chapter, int level) {
  CCScene* scene = GameScene::nodeWithChapter(chapter, level, 0);
  CCTransitionFade* fade = CCTransitionFade::transitionWithDuration(TRANSITION_LENGTH, scene);
  CCDirector::sharedDirector()->replaceScene(fade);
}

void ScreenManager::activateGrapplingHookRewardScreen(int chapter, int level) {
  CCScene* scene = GrapplingHookRewardScene::nodeWithChapter(chapter, level);
  CCTransitionFade* fade = CCTransitionFade::transitionWithDuration(TRANSITION_LENGTH, scene);
  CCDirector::sharedDirector()->replaceScene(fade);
}

void ScreenManager::activateParachuteRewardScreen(int chapter, int level) {
  CCScene* scene = ParachuteRewardScene::nodeWithChapter(chapter, level);
  CCTransitionFade* fade = CCTransitionFade::transitionWithDuration(TRANSITION_LENGTH, scene);
  CCDirector::sharedDirector()->replaceScene(fade);
}

void ScreenManager::loadAndDisplayGameScreen(int chapter, int level) {
  GameLoadingScene* scene = GameLoadingScene::nodeWithChapter(chapter, level);
  CCTransitionFade* fade = CCTransitionFade::transitionWithDuration(TRANSITION_LENGTH, scene);
  CCDirector::sharedDirector()->replaceScene(fade);
}

void ScreenManager::loadAndDisplayChapterIntroScreen(int chapter) {
  ChapterIntroLoadingScene* scene = ChapterIntroLoadingScene::nodeWithChapter(chapter);
  CCTransitionFade* fade = CCTransitionFade::transitionWithDuration(TRANSITION_LENGTH, scene);
  CCDirector::sharedDirector()->replaceScene(fade);
}

void ScreenManager::loadAndChaptersScreen(int chapter) {
  ChaptersLoadingScene* scene =  ChaptersLoadingScene::nodeWithChapter(chapter);
  CCTransitionFade* fade = CCTransitionFade::transitionWithDuration(TRANSITION_LENGTH, scene);
  CCDirector::sharedDirector()->replaceScene(fade);  
}

void ScreenManager::loadAndLevelsScreen(int chapter) {
  LevelsLoadingScene* scene = LevelsLoadingScene::nodeWithChapter(chapter);
  CCTransitionFade* fade = CCTransitionFade::transitionWithDuration(TRANSITION_LENGTH, scene);
  CCDirector::sharedDirector()->replaceScene(fade);    
}

void ScreenManager::loadAndDisplayEndGameScreen(int chapter) {
  EndGameLoadingScene* scene = EndGameLoadingScene::node(chapter);
  CCTransitionFade* fade = CCTransitionFade::transitionWithDuration(TRANSITION_LENGTH, scene);
  CCDirector::sharedDirector()->replaceScene(fade);      
}

void ScreenManager::transitionToGameScreen(int chapter, int level) {
  BackgroundCache().cacheBackgroundForNextLevel(chapter, level);
  CCScene* scene = GameTransitionScene::node(chapter, level);
  CCDirector::sharedDirector()->replaceScene(scene);
}

void ScreenManager::cutToGameScreen(int chapter, int level) {
  CCScene* scene = GameScene::nodeWithChapter(chapter, level, 0);
  CCDirector::sharedDirector()->replaceScene(scene);
}

#ifdef CHEATS
void ScreenManager::activateCheatsScreen() {
  CheatsScene* scene = CheatsScene::node();
  CCTransitionFade* fade = CCTransitionFade::transitionWithDuration(TRANSITION_LENGTH, scene);
  CCDirector::sharedDirector()->replaceScene(fade);    
}
#endif 

void ScreenManager::activateChaptersScreenUnlockChapter(int chapter) {
  ChaptersScene* scene = ChaptersScene::nodeWithChapter(chapter - 1);
  scene->scrollToChapter(chapter);
  CCTransitionFade* fade = CCTransitionFade::transitionWithDuration(TRANSITION_LENGTH, scene);
  CCDirector::sharedDirector()->replaceScene(fade);      
}

void ScreenManager::activateEndGameScreen(int chapter) {
  EndGameScene* scene = EndGameScene::node(chapter);
  CCTransitionFade* fade = CCTransitionFade::transitionWithDuration(TRANSITION_LENGTH, scene);
  CCDirector::sharedDirector()->replaceScene(fade);        
}

void ScreenManager::loadAndUnlockChapterScreen(int chapter) {
  ChapterUnlockedLoadingScene* scene = ChapterUnlockedLoadingScene::nodeWithChapter(chapter);
  CCTransitionFade* fade = CCTransitionFade::transitionWithDuration(TRANSITION_LENGTH, scene);
  CCDirector::sharedDirector()->replaceScene(fade);       
}
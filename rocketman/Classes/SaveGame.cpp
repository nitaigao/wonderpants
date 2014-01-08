  #include "SaveGame.h"

#include "Common.h"
#include "LevelCache.h"
#include "GameConfig.h"
#include "ChapterData.h"
#include "SaveState.h"

#include "json.h"

USING_NS_CC;

static SaveGame* _sharedSaveData = 0;

SaveGame* SaveGame::sharedSaveData() {
  if (!_sharedSaveData) {
    _sharedSaveData = new SaveGame();
  }
  return _sharedSaveData;
}

void SaveGame::cacheSaveData() {
  Array<ChapterData> chapterDatas = ChapterData::fromFile(GameConfig::chaptersFile());
  int chapter = 0;
  for(ChapterData chapterData : chapterDatas) {
    for (int level = 0; level < chapterData.levels(); level++) {
      String scorekey = String::withFormat("score_%d_%d", chapter, level);
      saveData_[scorekey] = CCUserDefault::sharedUserDefault()->getIntegerForKey(scorekey.c_str());
      
      String bonuskey = String::withFormat("bonus_%d_%d", chapter, level);
      saveData_[bonuskey] = CCUserDefault::sharedUserDefault()->getIntegerForKey(bonuskey.c_str());
      
      String coinskey = String::withFormat("coins_%d_%d", chapter, level);
      saveData_[coinskey] = CCUserDefault::sharedUserDefault()->getIntegerForKey(coinskey.c_str());
      
      String attemptskey = String::withFormat("attempts_%d_%d", chapter, level);
      saveData_[attemptskey] = CCUserDefault::sharedUserDefault()->getIntegerForKey(attemptskey.c_str());
      
      String timekey = String::withFormat("time_%d_%d", chapter, level);
      saveData_[timekey] = CCUserDefault::sharedUserDefault()->getIntegerForKey(timekey.c_str());
    }
    chapter++;
  }
}

void SaveGame::commit() {
  for (auto data : commitData_) {
    CCUserDefault::sharedUserDefault()->setIntegerForKey(data.first.c_str(), data.second);
  }
  commitData_.clear();
}

void SaveGame::purge() {
  Array<ChapterData> chapterDatas = ChapterData::fromFile(GameConfig::chaptersFile());
  int chapter = 0;
  for(ChapterData chapterData : chapterDatas) {
    for (int level = 0; level < chapterData.levels(); level++) {
      String bonuskey = String::withFormat("bonus_%d_%d", chapter, level);
      String coinskey = String::withFormat("coins_%d_%d", chapter, level);
      String attemptskey = String::withFormat("attempts_%d_%d", chapter, level);
      String timekey = String::withFormat("time_%d_%d", chapter, level);
      String scorekey = String::withFormat("score_%d_%d", chapter, level);
      SaveState saveState(chapter, level, 0, 0, 0, 0);
      saveProgress(saveState);
    }
    chapter++;
  }
  commit();
}

void SaveGame::saveProgress(const SaveState& saveState) {
  { 
    String scorekey = String::withFormat("score_%d_%d", saveState.chapterIndex(), saveState.levelIndex());
    saveData_[scorekey] = saveState.score();
    commitData_[scorekey] = saveState.score();
    
    String bonuskey = String::withFormat("bonus_%d_%d", saveState.chapterIndex(), saveState.levelIndex());
    saveData_[bonuskey] = saveState.bonus();
    commitData_[bonuskey] = saveState.bonus();
    
    String coinskey = String::withFormat("coins_%d_%d", saveState.chapterIndex(), saveState.levelIndex());
    saveData_[coinskey] = saveState.coins();
    commitData_[coinskey] = saveState.coins();
    
    String attemptskey = String::withFormat("attempts_%d_%d", saveState.chapterIndex(), saveState.levelIndex());
    saveData_[attemptskey] = saveState.attempts();
    commitData_[attemptskey] = saveState.attempts();
    
    String timekey = String::withFormat("time_%d_%d", saveState.chapterIndex(), saveState.levelIndex());
    saveData_[timekey] = saveState.levelTime();
    commitData_[timekey] = saveState.levelTime();
  }
}

int SaveGame::totalCoins() {
  int levelCount = ChapterData::totalLevelCount();
  int chapterCount = ChapterData::totalChapterCount();
  
  int totalCoins = 0;
  for (int chapter = 0; chapter < chapterCount; chapter++) {
    for (int level = 0; level < levelCount; level++) {
      String coinskey = String::withFormat("coins_%d_%d", chapter, level);
      totalCoins += saveData_[coinskey];
    }
  }
  return totalCoins;
}

int SaveGame::chapterScore(int chapter) {
  int levelCount = ChapterData::forChapter(chapter).levels();
  
  int totalScore = 0;
  for (int level = 0; level < levelCount; level++) {
    String coinskey = String::withFormat("score_%d_%d", chapter, level);
    totalScore += saveData_[coinskey];
  }
  return totalScore;  
}

bool SaveGame::getProgress(int levelIndex, int chapterIndex) {
  String scorekey = String::withFormat("score_%d_%d", chapterIndex, levelIndex);
  return saveData_[scorekey];
}

int SaveGame::getCoins(int levelIndex, int chapterIndex) {
  String coinskey = String::withFormat("coins_%d_%d", chapterIndex, levelIndex);
  return saveData_[coinskey];
}

int SaveGame::completedLevels(int chapter) {
  int count = 0;
  Array<ChapterData> chapterDatas = ChapterData::fromFile(GameConfig::chaptersFile());
  for (int level = 0; level < chapterDatas.objectAtIndex(chapter).levels(); level++) {
    String scorekey = String::withFormat("score_%d_%d", chapter, level);
    if (saveData_.find(scorekey) != saveData_.end()) {
      if (saveData_[scorekey]) {
        count++;
      }
    }
  }
  return count;
}

int SaveGame::getScore(int levelIndex, int chapterIndex) {
  int score = 0;
  String scorekey = String::withFormat("score_%d_%d", chapterIndex, levelIndex);
  if (saveData_.find(scorekey) != saveData_.end()) {
    score = saveData_[scorekey];
  }
  return score;  
}
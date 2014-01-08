#ifndef SaveGame_H_
#define SaveGame_H_

#include "cocos2d.h"

class SaveState;

class String;

class SaveGame {
  
public:
  
  static SaveGame* sharedSaveData();
  
public:
  
  void cacheSaveData();
  
  void commit();
  
  void purge();
  
public:
  
  void saveProgress(const SaveState& saveState);
  
  bool getProgress(int levelIndex, int chapterIndex);
  
  int getScore(int levelIndex, int chapterIndex);
  
  int getCoins(int levelIndex, int chapterIndex);
  
  int chapterScore(int chapter);
  
  int totalCoins();
  
  int completedLevels(int chapter);
  
private:
  
  std::map<String, int> saveData_;
  std::map<String, int> commitData_;
  
  
};

#endif

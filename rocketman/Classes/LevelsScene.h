#ifndef LevelsScene_H_
#define LevelsScene_H_

#include "Scene.h"

class LevelsScene : public Scene<LevelsScene> {
  
private:
  
  int chapter_;
  
public:
  
  static LevelsScene* nodeWithChapter(int chapter);
  
  void initWithChapter(int chapter);
  
  bool init();
  
  void back(CCObject* sender);
  
  void playLevel(CCObject* sender);
  
};

#endif

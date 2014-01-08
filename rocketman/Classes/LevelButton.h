#ifndef LevelButton_H_
#define LevelButton_H_

#include "cocos2d.h"

class LevelsScene;

class LevelButton : public cocos2d::CCMenuItem {
  
public:
  
  static LevelButton* node(LevelsScene* controller, int level);
  
  bool init(LevelsScene* controller, int level);
  
};

#endif

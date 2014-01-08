#ifndef GameUI_H_
#define GameUI_H_

#include "CCNode.h"
#include "IGameUI.h"

class GameScene;

class GameUI : public cocos2d::CCNode, public IGameUI {
  
public:
  
  static GameUI* nodeWithController(GameScene* controller, int chapter, int level);
  
  bool initWithController(GameScene* controller, int chapter, int level);
  
  void setBoost(float boost);
  
};

#endif

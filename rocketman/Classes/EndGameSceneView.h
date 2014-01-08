#ifndef EndGameSceneView_H_
#define EndGameSceneView_H_

#include "CCNode.h"

class EndGameScene;

class EndGameSceneView : public cocos2d::CCNode {
  
public:
  
  static EndGameSceneView* nodeWithController(EndGameScene* controller);
  
public:
  
  bool initWithController(EndGameScene* controller);
  
};

#endif

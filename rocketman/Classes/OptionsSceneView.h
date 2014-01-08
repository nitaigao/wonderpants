#ifndef OptionsSceneView_H_
#define OptionsSceneView_H_

#include "CCNode.h"

class OptionsScene;

class OptionsSceneView : public cocos2d::CCNode {
  
public:
  
  static OptionsSceneView* nodeWithController(OptionsScene* controller);
  
  void initWithController(OptionsScene* controller);
  
};

#endif

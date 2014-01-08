#ifndef CheatsSceneView_H_
#define CheatsSceneView_H_

#include "cocos2d.h"

class CheatsScene;

class CheatsSceneView : public cocos2d::CCNode {
  
public:
  
  static CheatsSceneView* nodeWithController(CheatsScene* controller);
  
  void initWithController(CheatsScene* controller);
  
};

#endif

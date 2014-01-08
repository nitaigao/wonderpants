#ifndef CreditsSceneView_H_
#define CreditsSceneView_H_

#include "CCNode.h"

class CreditsScene;

class CreditsSceneView : public cocos2d::CCNode {
  
public:
  
  static CreditsSceneView* nodeWithController(CreditsScene* controller);
  
  void initWithController(CreditsScene* controller);
  
};

#endif

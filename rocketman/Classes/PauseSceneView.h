#ifndef PauseSceneView_H_
#define PauseSceneView_H_

#include "CCNode.h"
#include "CCTouchDelegateProtocol.h"

class PauseScene;

class PauseSceneView : public cocos2d::CCNode, public cocos2d::CCTouchDelegate {
  
public:
  
  static PauseSceneView* nodeWithController(PauseScene* controller);
  
  bool initWithController(PauseScene* controller);
  
public:
  
  bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    
public:
  
  ~PauseSceneView();
  
};

#endif

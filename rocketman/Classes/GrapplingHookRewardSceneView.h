#ifndef GrapplingHookRewardSceneView_H_
#define GrapplingHookRewardSceneView_H_

#include "CCNode.h"
#include "CCTouchDelegateProtocol.h"

class GrapplingHookRewardScene;

class GrapplingHookRewardSceneView : public cocos2d::CCNode, public cocos2d::CCTargetedTouchDelegate {
  
public:
  
  static GrapplingHookRewardSceneView* nodeWithController(GrapplingHookRewardScene* controller);
  
public:
  
  bool initWithController(GrapplingHookRewardScene* controller);
  
  void characterFinished();
  
  void messageFinished();
  
  void update(cocos2d::ccTime dt);
  
  bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
  
  
private:
  
  GrapplingHookRewardScene* controller_;
  
};

#endif

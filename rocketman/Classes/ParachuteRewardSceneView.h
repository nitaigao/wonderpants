#ifndef ParachuteRewardSceneView_H_
#define ParachuteRewardSceneView_H_

#include "CCNode.h"
#include "CCTouchDelegateProtocol.h"

class ParachuteRewardScene;

class ParachuteRewardSceneView : public cocos2d::CCNode, public cocos2d::CCTargetedTouchDelegate {
  
public:
  
  static ParachuteRewardSceneView* nodeWithController(ParachuteRewardScene* controller);
  
public:
  
  bool initWithController(ParachuteRewardScene* controller);
  
  void characterFinished();
  
  void messageFinished();
  
  void update(cocos2d::ccTime dt);
  
  bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
  
  
private:
  
  ParachuteRewardScene* controller_;
  
};

#endif

#ifndef FollowAction_H_
#define FollowAction_H_

#include "cocos2d.h"

class FollowAction : public cocos2d::CCAction {
  
public:
  
  ~FollowAction();
  
public:
  
  static FollowAction* actionWithTarget(cocos2d::CCNode* target, cocos2d::CCPoint offset);
  
  FollowAction(cocos2d::CCNode* target, cocos2d::CCPoint offset);
  
public:
  
  void step(cocos2d::ccTime dt);
  
  bool isDone();
    
private:
  
  cocos2d::CCNode* followedNode_;
  cocos2d::CCPoint offset_;

};

#endif

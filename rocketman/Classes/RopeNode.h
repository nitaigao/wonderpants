#ifndef RopeNode_H_
#define RopeNode_H_

#include "cocos2d.h"

class RopeNode : public cocos2d::CCNode {
  
public:
  
  static RopeNode* node(cocos2d::CCNode* from, cocos2d::CCNode* to);
  
  RopeNode(cocos2d::CCNode* from, cocos2d::CCNode* to);
  
  void draw(void);
  
private:
  
  cocos2d::CCNode* from_;
  cocos2d::CCNode* to_;
  
};

#endif

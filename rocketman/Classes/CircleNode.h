#ifndef CircleNode_H_
#define CircleNode_H_

#include "cocos2d.h"

class CircleNode : public cocos2d::CCSprite {

public:
  
  static CircleNode* node(float radius);
  
  void initWithRadius(float radius);
  
  void draw();
  
private:
  
  std::vector<std::pair<cocos2d::CCPoint, cocos2d::CCPoint> > segments_;
  
};

#endif

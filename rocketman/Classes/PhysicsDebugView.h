#ifndef PhysicsDebugView_H_
#define PhysicsDebugView_H_

#include "cocos2d.h"

class Physics;

class PhysicsDebugView : public cocos2d::CCNode {
  
public:
  
  PhysicsDebugView(Physics* physics);
  
  static PhysicsDebugView* node(Physics* physics);
  
  void draw();
  
private:
  
  Physics* physics_;
  
};

#endif

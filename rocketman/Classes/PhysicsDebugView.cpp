#include "PhysicsDebugView.h"

#include "cocos2d.h"
USING_NS_CC;

#include "Physics.h"

PhysicsDebugView* PhysicsDebugView::node(Physics* physics) {
  PhysicsDebugView* node = new PhysicsDebugView(physics);
  node->autorelease();
  return node;
}

PhysicsDebugView::PhysicsDebugView(Physics* physics) : physics_(physics) {
  
}

void PhysicsDebugView::draw() {
  CCNode::draw();
  physics_->drawDebug();
}




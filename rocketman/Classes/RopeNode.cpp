#include "RopeNode.h"

USING_NS_CC;

RopeNode* RopeNode::node(cocos2d::CCNode* from, cocos2d::CCNode* to) {
  RopeNode* node = new RopeNode(from, to);
  node->autorelease();
  return node;
}

RopeNode::RopeNode(cocos2d::CCNode* from, cocos2d::CCNode* to) 
  : from_(from)
  , to_(to) { }

void RopeNode::draw(void) {
  removeAllChildrenWithCleanup(true);
  CCNode::draw();
  
  CCPoint pointA = from_->getPosition();
  CCPoint pointB = to_->getPosition();
  
  CCPoint diffVector = ccpSub(pointB, pointA);
  float distance = ccpLength(diffVector);
  
	int segmentFactor = 10; //increase value to have less segments per rope, decrease to have more segments
	int numPoints = distance / segmentFactor;
  
	float multiplier = distance / (numPoints-1);
  
  std::vector<CCPoint> vPoints;
  
	for(int i = 0;i < numPoints; i++) {
		CCPoint position = ccpAdd(pointA, ccpMult(ccpNormalize(diffVector), multiplier * i));
    vPoints.push_back(position);
  }
  
  for(int i = 0; i < numPoints - 1; i++) {
    CCPoint point1 = vPoints[i];
    CCPoint point2 = vPoints[i+1];
    
    CCPoint stickVector = ccpSub(point1, point2);
    float stickAngle = ccpToAngle(stickVector);
    
    CCSprite *tmpSprite = CCSprite::spriteWithSpriteFrameName("rope.png");
    
    ccTexParams params = {GL_LINEAR,GL_LINEAR,GL_REPEAT,GL_REPEAT};
    tmpSprite->getTexture()->setTexParameters(&params);
    tmpSprite->setPosition(ccpMidpoint(point1, point2));
    tmpSprite->setRotation(-1 * CC_RADIANS_TO_DEGREES(stickAngle));
    addChild(tmpSprite);
  }
}
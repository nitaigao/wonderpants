#include "CircleNode.h"

USING_NS_CC;


CircleNode* CircleNode::node(float radius) {
  CircleNode* node = new CircleNode();
  node->initWithRadius(radius);
  node->autorelease();
  return node;
}

void CircleNode::initWithRadius(float radius) {
  int segment_count = ceil(radius/2);
  int step = ceil(360/segment_count);
  int dash_width = ceil((M_PI * radius)/segment_count);
  
  CCPoint start = ccp(-dash_width/2,radius);
  CCPoint end = ccp(dash_width/2,radius);
  
  for (int i = 0; i < 360; i += step) {
    float angle = i * (M_PI/180);
    
    int new_start_x = (start.x * cos(angle)) - (start.y * sin(angle));
    int new_start_y = (start.x * sin(angle)) + (start.y * cos(angle));
    
    int new_end_x = (end.x * cos(angle)) - (end.y * sin(angle));
    int new_end_y = (end.x * sin(angle)) + (end.y * cos(angle));
    
    CCPoint new_start = ccp(new_start_x,new_start_y);
    CCPoint new_end = ccp(new_end_x,new_end_y);      

    auto part = std::make_pair(new_start, new_end);
    
    segments_.push_back(part);
  }
}

void CircleNode::draw() {
  CCSprite::draw();
  
  glColor4f(m_sColor.r/255, m_sColor.g/255, m_sColor.b/255, m_nOpacity/255.0f);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glLineWidth(2*CC_CONTENT_SCALE_FACTOR());
  glEnable(GL_LINE_SMOOTH);
  
  int length = segments_.size();
  
  for(int i = 0; i < length; i++){
    CCPoint x = segments_[i].first;
    CCPoint y = segments_[i].second;
    
    ccDrawLine(x, y);    
  } 
  
  glDisable(GL_LINE_SMOOTH);
  glBlendFunc(CC_BLEND_SRC, CC_BLEND_DST);
}



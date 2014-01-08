#include "CCSpriteCascadeVisible.h"

CCSpriteCascadeVisible* CCSpriteCascadeVisible::sprite() {
  CCSpriteCascadeVisible* sprite = new CCSpriteCascadeVisible();
  sprite->autorelease();
  return sprite;
}

void CCSpriteCascadeVisible::setIsVisible(bool isVisible) {
  CCSprite::setIsVisible(isVisible);
  CCObject* child = 0;
  CCARRAY_FOREACH(m_pChildren, child) {
    static_cast<CCSprite*>(child)->setOpacity(isVisible*255);
  }
}

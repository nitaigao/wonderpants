#ifndef SCENE_H
#define SCENE_H

#include "Macros.h"

#include "CCScene.h"

template <class T>
class Scene : public cocos2d::CCScene {
  
public:
  
  virtual ~Scene() { };
  
public:
  
  static T* node() {
    T *pRet = new T();
    if (pRet && pRet->init())
    {
      pRet->autorelease();
      return pRet;
    }
    
    SAFE_DELETE(pRet);
    
    return 0;
  };
  
public:
  
  virtual bool init() = 0;
  
};

#endif

#ifndef CCGB2ShapeCache_H_
#define CCGB2ShapeCache_H_

#include <string>

#include "cocos2d.h"
USING_NS_CC;

class b2Body;
class BodyDef;

class CCGB2ShapeCache {
  
public:
  
  static CCGB2ShapeCache* sharedCache();
  
  void addShapedWithFile(const char* plist);
  
  void addFixturedToBody(b2Body* body, const char* key);
  
private:
  
  CCMutableDictionary<std::string, CCString*> shapeFiles;
  CCMutableDictionary<std::string, BodyDef*> shapeObjects;
  
};

#endif

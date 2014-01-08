#ifndef PhysicsDataLoader_H_
#define PhysicsDataLoader_H_

class b2Body;
class String;

#include "CCGB2ShapeCache.h"

class PhysicsDataLoader {
  
public:
  
  void cache(const String& path) {
    CCGB2ShapeCache::sharedCache()->addShapedWithFile(path.c_str());
  };
  
  void loadBody(b2Body* body, const String& bodyKey) {
    CCGB2ShapeCache::sharedCache()->addFixturedToBody(body, bodyKey.c_str());
  };
};
  

#endif

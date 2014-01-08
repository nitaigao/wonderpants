#include "PhysicsDataLoader.h"

#include "Common.h"
#include "CCGB2ShapeCache.h"

void PhysicsDataLoader::cache(const String& path) {
  CCGB2ShapeCache::sharedCache()->addShapedWithFile(path.c_str());
}

void PhysicsDataLoader::loadBody(b2Body* body, const String& bodyKey) {
  CCGB2ShapeCache::sharedCache()->addFixturedToBody(body, bodyKey.c_str());
}
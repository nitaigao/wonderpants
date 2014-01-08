#ifndef RayCastLineOfSightResult_H_
#define RayCastLineOfSightResult_H_

#include "Box2D.h"

class RayCastLineOfSightResult : public b2RayCastCallback {
  
public:
  
  RayCastLineOfSightResult() : hits_(0) { };
  
  float32 ReportFixture(b2Fixture* fixture, const b2Vec2& point, const b2Vec2& normal, float32 fraction);
  
  inline int getHits() { return hits_; };
  
private:
  
  int hits_;
  
};


#endif

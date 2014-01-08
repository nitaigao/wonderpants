#include "RayCastLineOfSightResult.h"

float32 RayCastLineOfSightResult::ReportFixture(b2Fixture* fixture, const b2Vec2& point, const b2Vec2& normal, float32 fraction) {
  hits_++;
  return fraction;
}
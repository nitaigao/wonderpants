#include "LowPassAccelerometerFilter.h"

#include "cocos2d.h"
USING_NS_CC;

#define kUpdateFrequency 20  // Hz
#define kFilteringFactor 0.5

LowPassAccelerometerFilter::LowPassAccelerometerFilter()
  : accelerationX_(0)
  , accelerationY_(0) {
  
}

CCPoint LowPassAccelerometerFilter::addAcceleration(float x, float y) {
  accelerationX_ = x * kFilteringFactor + accelerationX_ * (1.0 - kFilteringFactor);
  accelerationY_ = y * kFilteringFactor + accelerationY_ * (1.0 - kFilteringFactor);
  return CCPointMake(accelerationX_, accelerationY_);
}
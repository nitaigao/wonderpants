#ifndef LowPassAccelerometerFilter_H_
#define LowPassAccelerometerFilter_H_

#include "cocos2d.h"

class LowPassAccelerometerFilter {
  
public:
  
  LowPassAccelerometerFilter();
  
  cocos2d::CCPoint addAcceleration(float x, float y);
  
private:
  
  float accelerationX_;
  float accelerationY_;
  
};

#endif

#ifndef Platform_H_
#define Platform_H_

#include "Common.h"

class Platform {
 
public:
 
 static shared_ptr<Platform> currentPlatform();
  
public:
  
  virtual ~Platform() { };
 
public:
 
 virtual String appPath() = 0;
 
public:
 
 virtual void vibrate() = 0;
  
public:
  
  long timeSinceEpoch();
 
};

#endif

#ifndef IOSPlatform_H_
#define IOSPlatform_H_

#include "Platform.h"

#define PLATFORM IOSPlatform

class IOSPlatform : public Platform {
  
public:
  
  String appPath();
  
  void vibrate();
  
};

#endif

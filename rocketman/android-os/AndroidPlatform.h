#ifndef AndroidPlatform_H_
#define AndroidPlatform_H_

#include "../Classes/Platform.h"
#include "SString.h"

#define PLATFORM AndroidPlatform

class AndroidPlatform : public Platform {
  
public:
  
  String appPath();
  
  void vibrate();
  
};

#endif

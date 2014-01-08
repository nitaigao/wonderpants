#include "Platform.h"

#ifdef __IPHONE_OS_VERSION_MAX_ALLOWED
  #include "IOSPlatform.h"
#else
  #include "AndroidPlatform.h"
#endif

#include <time.h>

shared_ptr<Platform> Platform::currentPlatform() {
  return shared_ptr<Platform>(new PLATFORM);
}

long Platform::timeSinceEpoch() {
  time_t t;
  time(&t);
  return t;
}
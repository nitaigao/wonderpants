#include "PerformanceTimer.h"

#include <sys/time.h>
#include <cstdio>
#include <string>

PerformanceTimer::PerformanceTimer(const char* name) : name_(name), startTime_(0) {
  start();
}

void PerformanceTimer::start() {
  startTime_ = timeNow();
}

void PerformanceTimer::stopAndReport() {
  float delta = (timeNow() - startTime_) / 1000000.0f;
  printf("%s %f\n", name_, delta);
}

long PerformanceTimer::timeNow() {
  struct timeval now;
  
  if(gettimeofday(&now, NULL) != 0) {
    return 0;
  }
  
  long timeNow = (now.tv_sec * 1000000) + now.tv_usec;
  
  return timeNow;
}

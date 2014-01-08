#include "Timer.h"
#include <time.h>

Timer::Timer() : startTime_(0), stopTime_(0) {
  
}

void Timer::start() {
  time_t t;
  time(&t);
  startTime_ = t;
}

void Timer::stop() {
  time_t t;
  time(&t);
  stopTime_ = t;
}

long Timer::split() {
  return stopTime_ - startTime_;
}

#ifndef PerformanceTimer_H_
#define PerformanceTimer_H_

class PerformanceTimer {
  
public:
  
  PerformanceTimer(const char* name);
  
  void start();
  
  void stopAndReport();
  
private:
  
  long timeNow();
  
  const char* name_;
  long startTime_;
  
};

#endif

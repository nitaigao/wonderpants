#ifndef Timer_H_
#define Timer_H_

class Timer {
  
public:
  
  Timer();
  
  void start();
  
  void stop();
  
  long split();
  
private:
  
  long startTime_;
  long stopTime_;
  
};

#endif

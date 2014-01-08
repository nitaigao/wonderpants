#ifndef SoundEffectLoadTask_H_
#define SoundEffectLoadTask_H_

#include "ILoadTask.h"
#include "Common.h"

class SoundEffectLoadTask : public ILoadTask {
  
public:
  
  SoundEffectLoadTask(const String& effectFile);
  
  void execute();
  
private:
  
  String effectFile_;
  
};

#endif

#ifndef MusicLoadTask_H_
#define MusicLoadTask_H_

#include "ILoadTask.h"
#include "Common.h"

class MusicLoadTask : public ILoadTask {
  
public:
  
  MusicLoadTask(const String& musicFile);
  
  void execute();
  
private:
  
  String musicFile_;
  
};

#endif

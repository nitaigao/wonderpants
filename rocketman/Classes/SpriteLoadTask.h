#ifndef SpriteLoadTask_H_
#define SpriteLoadTask_H_

#include "ILoadTask.h"
#include "Common.h"

class SpriteLoadTask : public ILoadTask {
  
public:
  
  SpriteLoadTask(const String& spriteFile);
  
  void execute();
  
private:
  
  String spriteFile_;
  
};

#endif

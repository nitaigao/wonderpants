#ifndef SpriteSheetLoadTask_H_
#define SpriteSheetLoadTask_H_

#include "Common.h"
#include "ILoadTask.h"

class SpriteSheetLoadTask : public ILoadTask {
  
public:
  
  SpriteSheetLoadTask(const String& spriteSheet);
  
  void execute();
  
private:
  
  String spriteSheet_;
  
};

#endif

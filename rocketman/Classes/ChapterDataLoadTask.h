#ifndef ChapterDataLoadTask_H_
#define ChapterDataLoadTask_H_

#include "ILoadTask.h"
#include "Common.h"

class ChapterDataLoadTask : public ILoadTask {
  
public:
  
  ChapterDataLoadTask(const String& dataFile);
  
  void execute();
  
private:
  
  String dataFile_;
  
};


#endif

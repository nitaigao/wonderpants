#ifndef TitleLoadList_H_
#define TitleLoadList_H_

#include <queue>
class ILoadTask;

class TitleLoadList {
  
public:
  
  static void fillLoadList(std::queue<ILoadTask*>& loadTasks);
  
};

#endif

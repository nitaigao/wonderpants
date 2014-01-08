#ifndef ILoadTask_H
#define ILoadTask_H

class ILoadTask {
  
public:
  
  virtual ~ILoadTask() { };
  
public:
  
  virtual void execute() = 0;
  
};

#endif

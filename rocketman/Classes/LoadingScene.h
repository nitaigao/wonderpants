#ifndef LoadingScene_H_
#define LoadingScene_H_

#include "ILoadTask.h"

#include <queue>
#include "cocos2d.h"

class LoadingScene : public cocos2d::CCScene {
  
public:
  
  virtual ~LoadingScene() { };
  
  LoadingScene();
  
public:
  
  bool init();
  
  void update(cocos2d::ccTime dt);
  
  void onEnterTransitionDidFinish();
  
  void load();
  
public:
  
  virtual void setupTasks() = 0;
  
  virtual void changeScene() = 0;
  
private:
  
  void setProgress(float progress);
  
  cocos2d::CCSprite* createProgress(int progress);
  
private:
  
  int fullTaskCount_;
  int frame_;
  
protected:
  
  std::queue<ILoadTask*> loadTasks_;
    
};

#endif

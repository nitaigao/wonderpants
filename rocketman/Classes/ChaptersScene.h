#ifndef ChaptersScene_H_
#define ChaptersScene_H_

#include "Scene.h"

class ChaptersScene : public Scene<ChaptersScene> {
  
public:
  
  static ChaptersScene* nodeWithChapter(int chapter);
  
  void initWithChapter(int chapter);
  
  bool init();
  
  void back(cocos2d::CCObject* sender);
  
  void selectChapter(cocos2d::CCObject* sender);
  
  void pageChanged(cocos2d::CCObject* sender);
  
  void scrollToChapter(int chapter);
  
};

#endif

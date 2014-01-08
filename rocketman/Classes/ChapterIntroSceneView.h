#ifndef ChapterIntroSceneView_H_
#define ChapterIntroSceneView_H_

#include "CCNode.h"

class ChapterIntroScene;

class ChapterIntroSceneView : public cocos2d::CCNode {
  
public:
  
  static ChapterIntroSceneView* nodeWithController(ChapterIntroScene* controller, int chapter);
  
  void initWithController(ChapterIntroScene* controller, int chapter);
  
};

#endif

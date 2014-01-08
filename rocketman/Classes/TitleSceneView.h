#ifndef __TITLE_SCENE_VIEW_H
#define __TITLE_SCENE_VIEW_H

#include "CCNode.h"

class TitleScene;

class TitleSceneView : public cocos2d::CCNode {
  
public:
  
  static TitleSceneView* nodeWithController(TitleScene* controller);
  
  void initWithController(TitleScene* controller);
  
};

#endif

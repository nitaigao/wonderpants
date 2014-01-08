#ifndef LevelSceneView_H_
#define LevelSceneView_H_

#include "CCNode.h"

class LevelsScene;
class ChapterData;

class LevelSceneView : public cocos2d::CCNode {
  
public:
  
  static LevelSceneView* nodeWithController(LevelsScene* controller, const ChapterData& chapterData);
  
  void initWithController(LevelsScene* controller, const ChapterData& chapterData);

  
};

#endif

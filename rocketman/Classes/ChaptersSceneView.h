#ifndef ChaptersSceneView_H_
#define ChaptersSceneView_H_

#include "CCNode.h"

class ChaptersScene;
class ChapterView;

class ChaptersSceneView : public cocos2d::CCNode {
  
public:
  
  static ChaptersSceneView* nodeWithController(ChaptersScene* controller);
  
  void initWithController(ChaptersScene* controller);
  
  void addChapterView(ChapterView* view);
  
  void setChapter(int chapter);
  
  void setCoins(int coins);
  
  void selectChapter(int chapter);
  
  void bounceComic(int chapter);
  
private:
  
  int chapters;
  
};

#endif

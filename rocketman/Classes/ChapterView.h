#ifndef ChapterView_H_
#define ChapterView_H_

#include "CCNode.h"

class ChapterData;
class ChaptersScene;

class ChapterView : public cocos2d::CCNode {
  
public:
  
  ChapterView();
  
  static ChapterView* viewWithData(const ChapterData& data, int score, int coins, ChaptersScene* controller);
  
public:
  
  void initWithData(const ChapterData& data, int score, int coins, ChaptersScene* controller);
  
public:
  
  void bounceComic();
  
  void chapterSelected(cocos2d::CCNode* sender);
  
private:
  
  void bounce(cocos2d::CCNode* node, float amount);
  
private:
  
  bool locked_;
  bool active_;
  
  SelectorProtocol *target;
  cocos2d::SEL_MenuHandler selector;
  
};

#endif

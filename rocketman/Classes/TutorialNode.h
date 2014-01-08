#ifndef TutorialNode_H_
#define TutorialNode_H_

#include "CCNode.h"
#include "CCTouchDelegateProtocol.h"
#include "Array.h"

class String;

class TutorialNode : public cocos2d::CCNode, public cocos2d::CCTouchDelegate {
  
public:
  
  static TutorialNode* node(const Array<String>& tutorials);
  
public:
  
  bool init();
  
  void ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
  
  bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    
private:
  
  void showTutorial();
  
  void removeNode(void* obj);
  
  void nextTutorial();
  
private:
  
  TutorialNode(const Array<String>& tutorials);
  
  ~TutorialNode();
  
private:
  
  int tutorialIndex_;
  Array<String> tutorials_;
  
};

#endif

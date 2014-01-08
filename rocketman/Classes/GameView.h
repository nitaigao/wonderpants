#ifndef GameView_H_
#define GameView_H_

#include "Common.h"
#include "CCNode.h"
#include "IGameView.h"

class String;
class RopeNode;

namespace cocos2d {
  class CCSprite;
  class CCPoint;
}

class GameView : public cocos2d::CCNode, public IGameView {
    
public:
  
  static GameView* node();
  
  void init();
  
public:
  
  void addSprite(const String& path, int x, int y, int z, float rotation, int label, Component* spatial, bool isVisible);
  
  void removeSprite(int label);
  
  void playAnimation(const String& animationName, int label, bool repeats, bool restoreLastFrame, AnimationCompleteHandler* callback);
  
  void panSceneY(int pixels);
  
  void shakeCamera();
  
  void addParticle(const String& data, int x, int y, int z, int offsetX, int offsetY, int label, Component* spatial);
  
  void emitParticle(int x, int y, const String& name, int label);
  
  void stopParticle(const String& name, int label);
  
  void fadeInSprite(int label, float duration);
  
  void fadeOutSprite(int label, float duration);
  
  void addFloatingLabel(int x, int y, int score);
  
  void addCircle(int x, int y, float radius, int label);
  
  void fadeInCircle(int label);
  
  void fadeOutCircle(int label);
  
  void fadeScene(const String& backgroundName);
  
  void createRope(int from, int to);
  
  void deleteRope();
  
  void addTutorials(const Array<String>& tutorials);
  
  void flipX(int label);
  
  void setVisible(bool isVisible, int label);
  
private:
  
  void update(cocos2d::ccTime dt);
  
private:
  
  Array<RopeNode*> ropes_;
  
};

#endif

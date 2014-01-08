#ifndef IGameView_H
#define IGameView_H

#include "Array.h"

class String;
class AnimationCompleteHandler;
class Component;

class IGameView {
  
public:
  
  virtual ~IGameView() { };
  
public:
  
  virtual void addSprite(const String& path, int x, int y, int z, float rotation, int label, Component* spatial, bool isVisible) = 0;
  
  virtual void removeSprite(int label) = 0;
  
  virtual void playAnimation(const String& animationName, int label, bool repeats, bool restoreLastFrame, AnimationCompleteHandler* callback) = 0;
  
  virtual void panSceneY(int pixels) = 0;
  
  virtual void shakeCamera() = 0;
  
  virtual void addParticle(const String& data, int x, int y, int z, int offsetX, int offsetY, int label, Component* spatial) = 0;
  
  virtual void emitParticle(int x, int y, const String& name, int label) = 0;
  
  virtual void stopParticle(const String& name, int label) = 0;
  
  virtual void fadeInSprite(int label, float duration) = 0;
  
  virtual void fadeOutSprite(int label, float duration) = 0;
  
  virtual void addFloatingLabel(int x, int y, int score) = 0;
  
  virtual void addCircle(int x, int y, float radius, int label) = 0;
  
  virtual void fadeInCircle(int label) = 0;
  
  virtual void fadeOutCircle(int label) = 0;
  
  virtual void createRope(int from, int to) = 0;

  virtual void deleteRope() = 0;
  
  virtual void addTutorials(const Array<String>& tutorials) = 0;
  
  virtual void flipX(int label) = 0;
  
  virtual void setVisible(bool isVisible, int label) = 0;
  
};

#endif

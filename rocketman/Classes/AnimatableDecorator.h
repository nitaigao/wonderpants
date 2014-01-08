#ifndef AnimatableDecorator_H_
#define AnimatableDecorator_H_

#include "Array.h"
#include "Value.h"
#include "String.h"

class Component;

class AnimatableDecorator {
  
public:
  
  AnimatableDecorator(Component* component);
  
public:
  
  int z() const;
  
  Array<Value> animations() const;
  
  String defaultAnimation() const;
  
  String defaultFrame() const;
  
  int label() const;
  
public:
  
  void cacheAnimations() const;
    
private:
  
  Component* component_;

};

#endif

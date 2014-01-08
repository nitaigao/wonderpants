#ifndef SpatialDecorator_H_
#define SpatialDecorator_H_

class Component;

class SpatialDecorator {
  
public:
  
  SpatialDecorator(Component* component);
  
public:
  
  float x();
  
  float y();
  
  int rotation();
  
private:
  
  Component* component_;
  
};

#endif

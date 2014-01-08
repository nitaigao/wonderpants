#ifndef Entity_H_
#define Entity_H_

#include "json.h"
#include "Array.h"

class Component;

class Entity {
  
public:
  
  void addComponent(Component* component);
  
  Array<Component*> components() { return components_; };
  
public:
  
  void prefabOverride();
  
private:
  
  Array<Component*> components_;
  
};

#endif

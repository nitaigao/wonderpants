#include "Entity.h"

#include "Macros.h"

#include "Component.h"
#include "Array.h"

void Entity::addComponent(Component* component) {
  components_.addObject(component);
}

void Entity::prefabOverride() {
  {
    bool foundOverridable = false;
    
    for (Component* component : components_) {
      Value v = component->type();
      String type = v.string();
      if (type != "spatial") continue;
      
      if (foundOverridable) {
        components_.removeObject(component);
        SAFE_DELETE(component);
        continue;
      }
      
      if (component->type() == "spatial") {
        foundOverridable = true;
      }
    }
  }
  
  {  
    Array<Component*> components = components_;
    
    for (Component* component : components) {
      if (component->type() != "script") continue;
      
      size_t nextIndex = components.indexOf(component) + 1;
      Array<Component*> belowMe = components.subArray(nextIndex, components.count() - nextIndex);
      
      for (Component* villain : belowMe) {
        if (villain->type() != "script") {
          continue;
        }
        
        if (component->attr("script").string() == villain->attr("script").string()) {
          villain->markForDeletion();
          components_.removeObject(villain);
        }
      }      
    }
    
    for (Component* component : components_) {
      if (component->isMarkedForDeletion()) {
        SAFE_DELETE(component);
      }
    }
  }
}

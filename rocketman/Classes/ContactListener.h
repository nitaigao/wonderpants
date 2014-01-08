#include "b2WorldCallbacks.h"

class Physics;
class Level;
class EventSystem;

class ContactListener : public b2ContactListener {
  
public:
  
  ContactListener(Physics* physics, Level* level, EventSystem* eventSystem)
  : physics_(physics)
  , level_(level)
  , eventSystem_(eventSystem)
  { };
  
  void BeginContact(b2Contact* contact);
  
private:
  
  Physics* physics_;
  Level* level_;
  EventSystem* eventSystem_;
  
  void registerHit(b2Fixture* source, b2Fixture* target, b2Contact* contact);
  
};

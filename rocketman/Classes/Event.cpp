#include "Event.h"

Event::Event(const String& type, const Array<Value> parameters) 
  : type_(type)
  , parameters_(parameters) {
  
}
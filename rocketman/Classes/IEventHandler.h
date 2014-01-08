#ifndef IEventHandler_H
#define IEventHandler_H

#include "Common.h"

class String;
class Value;

class IEventHandler {
  
public:
  
  virtual void onEvent(const String& event, const Array<Value>& parameters) = 0;
  
};

#endif

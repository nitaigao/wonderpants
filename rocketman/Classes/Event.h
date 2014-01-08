#ifndef EVENT_H
#define EVENT_H

#include "Value.h"
#include "Common.h"

class Event {
  
public:
  
  Event(const String& type, const Array<Value> parameters);
  
  inline String type() { return type_; };
  inline Array<Value> parameters() { return parameters_; };
  
private:
  
  String type_;
  Array<Value> parameters_;
  
};

#endif

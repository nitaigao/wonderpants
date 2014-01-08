#ifndef ComponentParser_H_
#define ComponentParser_H_

#include "Value.h"

class String;
class Component;

namespace Json { class Value; }

class ComponentParser {
      
public:
  
  Component* parse(Json::Value node);
  
private:
  
  void parse_(Component* component, Json::Value node);
  
  void parse_array(Array<Value>& array, Json::Value node);
  
  void parse_object(std::map<String, Value>& object, Json::Value node);
  
};

#endif

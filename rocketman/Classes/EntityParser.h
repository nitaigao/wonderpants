#ifndef EntityParser_H_
#define EntityParser_H_

#include "Common.h"

class String;
class Entity;

namespace Json { class Value; }

class EntityParser {
  
public:
  
  virtual ~EntityParser() { };
  
public:
  
  static shared_ptr<EntityParser> parser(const String& type);
    
public:
  
  virtual String type() = 0;
  
  virtual void parse(Entity* entity, const Json::Value& node) = 0;
  
};

#endif

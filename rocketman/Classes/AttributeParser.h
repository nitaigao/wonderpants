#ifndef AttributeParser_H_
#define AttributeParser_H_

#include "json.h"

class String;
class Level;

class AttributeParser {
  
public:
  
  static AttributeParser* parser(const String& key);
  
public:
  
  virtual ~AttributeParser() { };
  
public:
  
  virtual void parse(Level* level, const Json::Value& node) = 0;
  
  virtual String type() = 0;
  
};

#endif

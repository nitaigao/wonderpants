#ifndef DefaultEntityParser_H_
#define DefaultEntityParser_H_

#include "EntityParser.h"

class DefaultEntityParser : public EntityParser {

public:
  
  String type();
  
  void parse(Entity* entity, const Json::Value& node);
  
};

#endif

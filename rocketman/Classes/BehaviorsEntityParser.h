#ifndef BehaviorsEntityParser_H_
#define BehaviorsEntityParser_H_

#include "EntityParser.h"

class BehaviorsEntityParser : public EntityParser {
  
public:
  
  String type();
  
  void parse(Entity* entity, const Json::Value& node);
  
};

#endif

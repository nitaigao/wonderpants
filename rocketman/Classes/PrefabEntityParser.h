#ifndef PrefabEntityParser_H_
#define PrefabEntityParser_H_

#include "EntityParser.h"

class PrefabEntityParser : public EntityParser {

public:
  
  String type();
  
  void parse(Entity* entity, const Json::Value& node);
  
};

#endif

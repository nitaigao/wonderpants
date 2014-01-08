#ifndef LevelsParser_H_
#define LevelsParser_H_

class String;
class Level;
class Entity;

namespace Json { class Value; }

#include "json.h"

class LevelsParser {
  
public:
  
  void levelsFromFile(const String& path, Level* level);
  
  void parseEntity(const Json::Value& json, Entity* entity);
  
};

#endif

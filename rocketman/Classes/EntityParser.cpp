#include "EntityParser.h"

#include "Common.h"

#include "DefaultEntityParser.h"
#include "BehaviorsEntityParser.h"
#include "PrefabEntityParser.h"

shared_ptr<EntityParser> EntityParser::parser(const String& type) {
  if (type == "behaviors") {
    return shared_ptr<EntityParser>(new BehaviorsEntityParser);
  }
  if (type == "src") {
    return shared_ptr<EntityParser>(new PrefabEntityParser);
  }
  return shared_ptr<EntityParser>(new DefaultEntityParser);
}

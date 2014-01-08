#include "DefaultEntityParser.h"

#include "Common.h"

#include "json.h"
#include "Entity.h"

#include "cocos2d.h"

String DefaultEntityParser::type() {
  return "default";
}

void DefaultEntityParser::parse(Entity* entity, const Json::Value& node) {
  CCLOG("couldnt parse entity node %s", node.toStyledString().c_str());
}

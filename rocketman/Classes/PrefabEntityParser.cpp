#include "PrefabEntityParser.h"

#include "Common.h"
#include "json.h"
#include "EntityParser.h"
#include "CCFileUtils.h"
#include "Component.h"
#include "Entity.h"

USING_NS_CC;

String PrefabEntityParser::type() {
  return "src";
}

void PrefabEntityParser::parse(Entity* entity, const Json::Value& node) {
  String path = node.asString();
  String fullPath = CCFileUtils::fullPathFromRelativePath(path.c_str());
  String json = String::fromFile(fullPath);
  
  Json::Reader reader;
  Json::Value root;
  
  reader.parse(json.str(), root);
  
  Json::Value::Members members = root.getMemberNames();
  
  for (int i = 0; i < members.size(); ++i) {
    shared_ptr<EntityParser> parser = EntityParser::parser(members[i]);
    Json::Value data = root[parser->type().c_str()];
    parser->parse(entity, data);
  }
  
  entity->prefabOverride();
}
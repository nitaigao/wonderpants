#include "LevelsParser.h"

#include "Common.h"

#include "Level.h"
#include "Entity.h"
#include "Component.h"

#include "AttributeParser.h"
#include "EntityParser.h"
#include "ComponentParser.h"

#include "ResourceCache.h"

#include "json.h"

void LevelsParser::levelsFromFile(const String& path, Level* level) {
  String json = ResourceCache::sharedCache()->loadString(path.c_str());
  Json::Reader reader;
  Json::Value root;
  reader.parse(json.str(), root);
      
  Json::Value attributesJson = root["attributes"];
  for (int i = 0; i < attributesJson.size(); ++i) {
    String member = attributesJson.getMemberNames()[i];
    AttributeParser* parser = AttributeParser::parser(member);
    Json::Value attribute = attributesJson[parser->type().c_str()];
    parser->parse(level, attribute);
    SAFE_DELETE(parser);
  }
  
  Json::Value entitiesJson = root["entities"];
  for (int i = 0; i < entitiesJson.size(); ++i) {
    Json::Value entityJson = entitiesJson[i];
    Entity* entity = new Entity();
    parseEntity(entityJson, entity);
    level->addEntity(entity);
    SAFE_DELETE(entity);
  }        
}

void LevelsParser::parseEntity(const Json::Value& json, Entity* entity) {
  using namespace Json;
  Json::Value::Members members = json.getMemberNames();
  
  for (int i = 0; i < members.size(); ++i) {
    String member = members[i];
    shared_ptr<EntityParser> parser = EntityParser::parser(member);
    Json::Value data = json[parser->type().c_str()];
    parser->parse(entity, data);
  }
}

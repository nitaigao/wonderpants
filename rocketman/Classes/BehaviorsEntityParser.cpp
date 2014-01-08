#include "BehaviorsEntityParser.h"

#include "Common.h"

#include "json.h"

#include "ComponentParser.h"
#include "Component.h"
#include "Entity.h"

String BehaviorsEntityParser::type() {
  return "behaviors";
}

void BehaviorsEntityParser::parse(Entity* entity, const Json::Value& node) {
  using namespace Json;

  //TODO: Pull in Component Parser code into behaviors parser
  for (int i = 0; i < node.size(); ++i) {
    Json::Value componentJson = node[i];
    ComponentParser parser;
    Component* component = parser.parse(componentJson);
    entity->addComponent(component);
  }
}
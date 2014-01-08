#include "TutorialAttributeParser.h"

#include "Common.h"
#include "Level.h"

void TutorialAttributeParser::parse(Level* level, const Json::Value& node) {
  for (int i = 0; i < node.size(); ++i) {
    String tutorial = node[i].asString();
    level->addTutorial(tutorial);
  }
}

String TutorialAttributeParser::type() {
  return "tutorial";
}

#include "AttributeParser.h"

#include "Common.h"

#include "TutorialAttributeParser.h"

AttributeParser* AttributeParser::parser(const String& key) {
  if (key == "tutorial") {
    return new TutorialAttributeParser();
  }
  return 0;
}
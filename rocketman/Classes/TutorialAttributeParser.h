#ifndef TutorialAttributeParser_H_
#define TutorialAttributeParser_H_

#include "AttributeParser.h"

class Level;

class TutorialAttributeParser : public AttributeParser {
  
public:
  
  void parse(Level* level, const Json::Value& node);
  
  String type();
    
};

#endif

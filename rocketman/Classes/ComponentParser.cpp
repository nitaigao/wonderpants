#include "ComponentParser.h"

#include "Component.h"
#include "json.h"
#include "Common.h"
#include "Value.h"

#include "cocos2d.h"
USING_NS_CC;

void ComponentParser::parse_object(std::map<String, Value>& object, Json::Value node) {
  Json::Value::Members members = node.getMemberNames();
  for (int i = 0; i < node.size(); ++i) {
    
    String member = members[i];
    Json::Value value = node[member.c_str()];
    
    switch (value.type()) {
      case Json::intValue: {
        object[member] = value.asInt();
        break;
      }
      case Json::uintValue: {
        object[member] = value.asUInt();
        break;
      }
      case Json::realValue: {
        object[member] = (float)value.asDouble();
        break;
      }
      case Json::stringValue: {
        object[member] = value.asString().c_str();
        break;
      }
      case Json::arrayValue: {
        Array<Value> values;
        parse_array(values, value);
        object[member] = values;
        break;
      }
      case Json::objectValue: {
        std::map<String, Value> map;
        parse_object(map, value);
        object[member] = map;
        break;
      }
        
      default: break;
    }
  }    
}


void ComponentParser::parse_array(Array<Value>& array, Json::Value node) {
  for (int i = 0; i < node.size(); ++i) {    
    Json::Value value = node[i];
    
    switch (value.type()) {
      case Json::intValue: {
        array.addObject(value.asInt());
        break;
      }
      case Json::uintValue: {
        array.addObject(value.asUInt());
        break;
      }
      case Json::realValue: {
        array.addObject((float)value.asDouble());
        break;
      }
      case Json::stringValue: {
        array.addObject(value.asString().c_str());
        break;
      }
      case Json::arrayValue: {
        Array<Value> values;
        parse_array(values, value);
        array.addObject(values);
        break;
      }
      case Json::objectValue: {
        std::map<String, Value> map;
        parse_object(map, value);
        array.addObject(map);
        break;
      }
        
      default: break;
    }
  }    
}

void ComponentParser::parse_(Component* component, Json::Value node) {
  Json::Value::Members members = node.getMemberNames();
  for (int i = 0; i < node.size(); ++i) {
    
    String member = members[i];
    Json::Value value = node[member.c_str()];
    
    if (component->type() == "spatial") {
      if (member == "x" || member == "y") {
        component->setAttr(member, float(value.asInt()));
        continue;
      }
    }
    
    switch (value.type()) {
      case Json::intValue: {
        component->setStringAttr(member, value.asInt());
        break;
      }
      case Json::uintValue: {
        component->setStringAttr(member, value.asUInt());
        break;
      }
      case Json::realValue: {
        component->setStringAttr(member, (float)value.asDouble());
        break;
      }
      case Json::stringValue: {
        String v = value.asString();
        component->setStringAttr(member, v);
        break;
      }
      case Json::booleanValue: {
        bool v = value.asBool();
        component->setStringAttr(member, v);
        break;
      }
      case Json::arrayValue: {
        Array<Value> values;
        parse_array(values, value);
        component->setStringAttr(member, values);
        break;
      }
      case Json::objectValue: {
        std::map<String, Value> values;
        parse_object(values, value);
        component->setStringAttr(member, values);
        break;
      }
        
      default: 
        CCLOG("failed to parse %s in %s", member.c_str(), node.toStyledString().c_str());
        
        break;
    }
  }  
}

Component* ComponentParser::parse(Json::Value node) {
  Component* component = new Component();
  component->setType(node["type"].asString().c_str());
  this->parse_(component, node);
  return component;
}
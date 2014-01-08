#ifndef AttributeScriptHandler_H_
#define AttributeScriptHandler_H_

#include "ScriptHandler.h"

class Component;
class lua_State;
class Level;
class String;
class Value;

class AttributeScriptHandler : public ScriptHandler {
  
public:
  
  AttributeScriptHandler(lua_State* state, Component* component, Level* level);
  
  Value getAttr(const String& key, int label, const String& type);
  
  void setAttr(const String& key, const Value& value, int label, const String& type);
  
  static int lua_getAttr(lua_State* l);
  
  static int lua_setAttr(lua_State* l);
    
private:
  
  Component* component_;
  lua_State* l_;
  Level* level_;
   
};

#endif

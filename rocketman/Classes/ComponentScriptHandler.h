#ifndef ComponentScriptHandler_H_
#define ComponentScriptHandler_H_

#include "ScriptHandler.h"
#include "Array.h"

class lua_State;
class Component;
class Level;
class String;

class ComponentScriptHandler : public ScriptHandler {
  
public:
  
  ComponentScriptHandler(lua_State* state, Component* component, Level* level);
  
private:
  
  static int lua_getComponent(lua_State* l);
  Component* getComponent(const String& type, int label);
  
  static int lua_getComponents(lua_State* l);
  Array<Component*> getComponents(const String& type);
  
private:
  
  lua_State* l_;
  Component* component_;
  Level* level_;
  
};

#endif

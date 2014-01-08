#ifndef EntityScriptHandler_H_
#define EntityScriptHandler_H_

#include "ScriptHandler.h"

class lua_State;
class Level;
class Component;
class String;

class EntityScriptHandler : public ScriptHandler {
  
public:
  
  EntityScriptHandler(lua_State* state, Component* component, Level* level);
  
private:
  
  static int l_destroy(lua_State* l);
  void destroy(int label);
  
  static int l_spawn(lua_State* l);
  int spawn(const String& type, float x, float y, int rotation);
  
private:
  
  Level* level_;
  Component* component_;
  
};

#endif

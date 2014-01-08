#ifndef TransformScriptHandler_H_
#define TransformScriptHandler_H_

#include "ScriptHandler.h"

class lua_State;
class Component;
class Physics;

class TransformScriptHandler : public ScriptHandler {
  
public:
  
  TransformScriptHandler(lua_State* state, Component* component, Physics* physics);
  
private:
  
  static int l_setTranslation(lua_State* l);
  void setTranslation(float x, float y, int label);
  
  static int l_translate(lua_State* l);
  void translate(float x, float y, int label);
  
  static int l_setRotation(lua_State* l);
  void setRotation(float rotation);
  
  
  static int l_rotate(lua_State* l);
  void rotate(float rotation);
  
  static int l_lookAt(lua_State* l);
  void lookAt(int offset, int target);
  
  
  static int l_stopLookAt(lua_State* l);
  
private:
  
  Component* component_;
  Physics* physics_;
  
  
};

#endif

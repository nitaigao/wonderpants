#ifndef ParticlesScriptHandler_H_
#define ParticlesScriptHandler_H_

#include "ScriptHandler.h"

class lua_State;
class String;
class IGameView;

class ParticlesScriptHandler : public ScriptHandler {
  
public:

  ParticlesScriptHandler(lua_State* state, IGameView* view);
  
  void emit(int x, int y, const String& name, int label);
  
  void stop(const String& name, int label);
  
private:
  
  static int l_emit(lua_State* l);
  
  static int l_stop(lua_State* l);
  
private:
  
  IGameView* view_;
  
};

#endif

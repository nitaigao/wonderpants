#ifndef LuaState_H_
#define LuaState_H_

#include "Array.h"

class lua_State;
class String;
class Value;
class Component;
class Level;

class ScriptHandler;
class IGetSetDelegate;
class EventSystem;
class IGameUI;
class IGameView;
class Physics;
class PlayerState;

typedef int (IGetSetDelegate::*lua_CPPFunction) (lua_State *L);

class LuaState {
  
public:
    
  ~LuaState();
  
public:
  
  static LuaState* state(Component* component, 
                         EventSystem* eventSystem, 
                         Level* level, 
                         IGameUI* ui, 
                         IGameView* view, 
                         Physics* physics,
                         PlayerState* playerState);
  
public:
    
  void setup();
  
  void loadScript(const String& path);
  
  void setGlobal(const String& key, const Value& value);
  
  void setTable(const String& table, const String& key, const Value& value);
  
  void run();
  
  void update(float dt);
  
  void addScriptHandler(ScriptHandler* handler);
  
public:
  
  inline int getTag() { return tag_; };
  
  inline void setTag(int tag) { tag_ = tag; };
  
public:
  
  inline void markForDeletion() { isMarkedForDeletion_ = true; };
  
  inline bool isMarkedForDeletion() { return isMarkedForDeletion_; };
  
private:
  
  LuaState(lua_State* l);
  
private:
  
  lua_State* l_;
  Array<ScriptHandler*> handlers_;
  int tag_;

private:
  
  void setGameState(lua_State* l_);
  
private:
  
  bool isMarkedForDeletion_;
  
};

#endif

#ifndef StateCache_H_
#define StateCache_H_

class String;
class LuaState;
class Level;

class StateCache {
  
public:
  
  static StateCache* sharedCache();
  
public:
  
  LuaState* stateForPath(const String& path, Level* level);
  
private:
  
  void init();
  
};

#endif

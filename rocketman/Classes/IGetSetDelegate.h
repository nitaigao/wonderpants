#ifndef IGetSetDelegate_H
#define IGetSetDelegate_H

class lua_State;

class IGetSetDelegate {
  
public:
  
  virtual int getAttr(lua_State*) = 0;
  
  virtual int setAttr(lua_State*) = 0;
   
};

#endif

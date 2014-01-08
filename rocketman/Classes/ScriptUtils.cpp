#include "ScriptUtils.h"

CCPoint lua_tovector(lua_State *l, int idx) {
  lua_pushstring(l, "x");
  lua_gettable(l, idx - 1);
  float x = lua_tonumber(l, LUA_STACK_TOP);
  lua_pop(l, 1);
  
  lua_pushstring(l, "y");
  lua_gettable(l, idx - 1);
  float y = lua_tonumber(l, LUA_STACK_TOP);
  lua_pop(l, 1);
  
  return CCPointMake(x, y);
}

ccColor3B lua_tocolor(lua_State *l, int idx) {
  lua_pushstring(l, "r");
  lua_gettable(l, idx - 1);
  float r = lua_tonumber(l, LUA_STACK_TOP);
  lua_pop(l, 1);
  
  lua_pushstring(l, "g");
  lua_gettable(l, idx - 1);
  float g = lua_tonumber(l, LUA_STACK_TOP);
  lua_pop(l, 1);
  
  lua_pushstring(l, "b");
  lua_gettable(l, idx - 1);
  float b = lua_tonumber(l, LUA_STACK_TOP);
  lua_pop(l, 1);
  
  return ccc3(r, g, b);
}

void lua_pushvector(lua_State *l, int x, int y) {
  lua_newtable(l);
  
  lua_pushstring(l, "x");
  lua_pushinteger(l, x);
  lua_settable(l, -3);
  
  
  lua_pushstring(l, "y");
  lua_pushinteger(l, y);
  lua_settable(l, -3);
}
#ifndef rocketman_ScriptUtils_h
#define rocketman_ScriptUtils_h

extern "C" {
  #include "lua.h"
  #include "lualib.h"
  #include "lauxlib.h"
};

#include "Common.h"

#include "cocos2d.h"
USING_NS_CC;

#include "ResourceCache.h"
#include "Value.h"
#include "Component.h"
#include "AttributeScriptHandler.h"

static const int LUA_STACK_TOP = -1;
static const int LUA_BASE_TABLE_COUNT = 1;

static void stackDump (lua_State *L) {
  int i;
  int top = lua_gettop(L);
  for (i = 1; i <= top; i++) {  /* repeat for each level */
    int t = lua_type(L, i);
    switch (t) {
        
      case LUA_TSTRING:  /* strings */
        printf("`%s'", lua_tostring(L, i));
        break;
        
      case LUA_TBOOLEAN:  /* booleans */
        printf(lua_toboolean(L, i) ? "true" : "false");
        break;
        
      case LUA_TNUMBER:  /* numbers */
        printf("%g", lua_tonumber(L, i));
        break;
        
      default:  /* other values */
        printf("%s", lua_typename(L, t));
        break;
        
    }
    printf("  ");  /* put a separator */
  }
  printf("\n");  /* end the listing */
}

static void dumpError(int result, lua_State* l) {
  if (result) {
    String errorMessage = lua_tostring(l, -1);
    CCLOG("%s", errorMessage.c_str());
    lua_pop(l, 1);
  }
}

static void callProtected(lua_State* state, int args, int results) {
  int result = lua_pcall(state, args, results, 0);
  dumpError(result, state);
}

static void loadScript_(lua_State* l, const char* path) {
  CCFileData* data = ResourceCache::sharedCache()->loadBinary(path);
  unsigned long nSize  = data->getSize();
  unsigned char* pBuffer = data->getBuffer();
  int error = luaL_loadbuffer(l, (char*)pBuffer, nSize, 0);
  dumpError(error, l);
  callProtected(l, 0, LUA_MULTRET);   
}

static void lua_pushvalue(lua_State* l, const Value& value) {
  switch (value.type()) {
    case Value::NullValue:
      lua_pushnil(l);
      break;
    case Value::BoolValue:
      lua_pushboolean(l, value.boolValue());
      break;
    case Value::StringValueType:
      lua_pushstring(l, value.string().c_str());
      break;
    case Value::IntValue:
      lua_pushinteger(l, value.intValue());
      break;
    case Value::FloatValue:
      lua_pushnumber(l, value.floatValue());
      break;
    case Value::UIntValue:
      lua_pushinteger(l, value.intValue());
      break;
    default:
      CCLog("type not supported");
      break;
  }   
}

static Value lua_tovalue(lua_State* l, int idx) {
  
  if (lua_isnumber(l, idx)) {
    return (float)lua_tonumber(l, idx);
  }
  
  if (lua_isboolean(l, idx)) {
    return (bool)lua_toboolean(l, idx);
  }
  
  if (lua_isstring(l, idx)) {
    return lua_tostring(l, idx);
  }
  
  return Value();
}

static void pushComponent(lua_State* l, Component* component) {
  if (!component) {
    lua_pushnil(l);
  } else {
    lua_newtable(l);  
    lua_pushstring(l, "label");
    lua_pushnumber(l, component->label());
    lua_settable(l, -3);
    
    lua_pushstring(l, "type");
    lua_pushstring(l, component->type().c_str());
    lua_settable(l, -3);
    
    lua_newtable(l);
    lua_pushcfunction(l, AttributeScriptHandler::lua_getAttr);
    lua_setfield(l, -2, "__index");
    lua_pushcfunction(l, AttributeScriptHandler::lua_setAttr);
    lua_setfield(l, -2, "__newindex");
    lua_setmetatable(l, -2);
  }
}

template <class T>
static T* handler(lua_State* l, const char* name) {
  lua_pushstring(l, name);
  lua_gettable(l, LUA_REGISTRYINDEX);
  
  T* handler = (T*)lua_touserdata(l, -1);
  lua_pop(l, 1); 
  
  return handler;
}

void lua_pushvector(lua_State *l, int x, int y);
CCPoint lua_tovector(lua_State *l, int idx);
ccColor3B lua_tocolor(lua_State *l, int idx);

#endif

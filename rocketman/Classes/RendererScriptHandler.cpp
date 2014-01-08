#include "RendererScriptHandler.h"

#include "Macros.h"

#include "ScriptUtils.h"
#include "ScriptAnimationCompleteHandler.h"
#include "DefaultAnimationCompleteHandler.h"
#include "Component.h"
#include "IGameView.h"

extern "C" {
  #include "lua.h"
  #include "lualib.h"
  #include "lauxlib.h"
};

RendererScriptHandler::RendererScriptHandler(lua_State* state, Component* component, IGameView* view) 
  : component_(component)
  , view_(view) {
  lua_newtable(state);
  
  lua_pushstring(state, "fade_out");
  lua_pushcfunction(state, l_fadeOut);
  lua_settable(state, -3);
  
  lua_pushstring(state, "fade_in");
  lua_pushcfunction(state, l_fadeIn);
  lua_settable(state, -3);
  
  lua_pushstring(state, "continuous_rotate");
  lua_pushcfunction(state, l_continuousRotate);
  lua_settable(state, -3);
  
  lua_pushstring(state, "follow");
  lua_pushcfunction(state, l_follow);
  lua_settable(state, -3);
  
  lua_pushstring(state, "play_animation");
  lua_pushcfunction(state, l_playAnimation);
  lua_settable(state, -3);
  
  lua_pushstring(state, "remove_visible");
  lua_pushcfunction(state, l_removeVisible);
  lua_settable(state, -3);
  
  lua_pushstring(state, "remove_animable");
  lua_pushcfunction(state, l_removeAnimable);
  lua_settable(state, -3);
  
  lua_pushstring(state, "shake_camera");
  lua_pushcfunction(state, l_shakeCamera);
  lua_settable(state, -3);
  
  lua_pushstring(state, "on_screen");
  lua_pushcfunction(state, l_onScreen);
  lua_settable(state, -3);
  
  lua_pushstring(state, "flip_x");
  lua_pushcfunction(state, l_flipX);
  lua_settable(state, -3);
  
  lua_pushstring(state, "set_visible");
  lua_pushcfunction(state, l_setVisible);
  lua_settable(state, -3);
  
  lua_pushstring(state, "fade_in_swing_circle");
  lua_pushcfunction(state, l_fadeInSwingCircle);
  lua_settable(state, -3);
  
  lua_pushstring(state, "fade_out_swing_circle");
  lua_pushcfunction(state, l_fadeOutSwingCircle);
  lua_settable(state, -3);
  
  lua_pushstring(state, "screen_size");
  lua_pushcfunction(state, l_screenSize);
  lua_settable(state, -3);
  
  lua_setglobal(state, "renderer");
  
  lua_pushstring(state, "renderer");
  lua_pushlightuserdata(state, this);
  lua_settable(state, LUA_REGISTRYINDEX);
}

int RendererScriptHandler::l_fadeOut(lua_State* l) {  
  float duration = lua_tonumber(l, LUA_STACK_TOP);
  lua_pop(l, 1);
  
  handler<RendererScriptHandler>(l, "renderer")->fadeOut(duration);
  
  return 0;
}

void RendererScriptHandler::fadeOut(float duration) {
  view_->fadeOutSprite(component_->label(), duration);
}

int RendererScriptHandler::l_fadeIn(lua_State* l) {  
  float duration = lua_tonumber(l, LUA_STACK_TOP);
  lua_pop(l, 1);
  
  handler<RendererScriptHandler>(l, "renderer")->fadeIn(duration);

  return 0;
}

void RendererScriptHandler::fadeIn(float duration) {
  view_->fadeInSprite(component_->label(), duration);
}

int RendererScriptHandler::l_continuousRotate(lua_State* l) {
  return 0;
}

int RendererScriptHandler::l_follow(lua_State* l) {
  return 0;
}

int RendererScriptHandler::l_playAnimation(lua_State* l) {
  AnimationCompleteHandler* completeCallback = DefaultAnimationCompleteHandler::handler();
  
  if (lua_gettop(l) == 5) {
    int ref = luaL_ref(l, LUA_REGISTRYINDEX);  
    SAFE_DELETE(completeCallback);
    completeCallback = ScriptAnimationCompleteHandler::handler(l, ref);
  }
  
  bool restoreLastFrame = true;
  
  if (lua_gettop(l) == 4) {
    restoreLastFrame = lua_toboolean(l, -1);
    lua_pop(l, 1);
  }
  
  bool repeats = false;
  
  if (lua_gettop(l) == 3) {
    repeats = lua_toboolean(l, -1);
    lua_pop(l, 1);
  }
  
  String animationName = lua_tostring(l, -1);
  lua_pop(l, 1);
  
  lua_pushstring(l, "renderer");
  lua_gettable(l, LUA_REGISTRYINDEX);
  
  RendererScriptHandler* handler = (RendererScriptHandler*)lua_touserdata(l, -1);
  lua_pop(l, 1);

  handler->playAnimation(animationName, repeats, restoreLastFrame, completeCallback);
  
  return 0;
}

void RendererScriptHandler::playAnimation(const String& animationName, bool repeats, bool restoreLastFrame, AnimationCompleteHandler* callback) {
  view_->playAnimation(animationName, component_->label(), repeats, restoreLastFrame, callback);
}

int RendererScriptHandler::l_removeVisible(lua_State* l) {
  int label = lua_tonumber(l, -1);
  lua_pop(l, 1);

  handler<RendererScriptHandler>(l, "renderer")->removeVisible(label);

  return 0;
}

void RendererScriptHandler::removeVisible(int label) {
  view_->removeSprite(label);
}

int RendererScriptHandler::l_removeAnimable(lua_State* l) {
  int label = lua_tonumber(l, -1);
  lua_pop(l, 1);

  handler<RendererScriptHandler>(l, "renderer")->removeAnimable(label);
  
  return 0;
}

void RendererScriptHandler::removeAnimable(int label) {
  view_->removeSprite(label);
}

int RendererScriptHandler::l_shakeCamera(lua_State* l) {
  handler<RendererScriptHandler>(l, "renderer")->shakeCamera();
  return 0;
}

void RendererScriptHandler::shakeCamera() {
  view_->shakeCamera();
}

int RendererScriptHandler::l_onScreen(lua_State* l) {
  int y = lua_tonumber(l, -1);
  lua_pop(l, 1);
  int x = lua_tonumber(l, -1);
  lua_pop(l, 1);
  
  CCSize winSize = CCDirector::sharedDirector()->getWinSize();;
  
  bool result =  (x < winSize.width && x > 0 && y < winSize.height && y > 0);
  lua_pushboolean(l, result);
  
  return 1;
}

int RendererScriptHandler::l_flipX(lua_State* l) {
  int label = lua_tonumber(l, -1);
  lua_pop(l, 1);
  handler<RendererScriptHandler>(l, "renderer")->flipX(label);
  return 0;
}

void RendererScriptHandler::flipX(int label) {
  view_->flipX(label);
}

int RendererScriptHandler::l_setVisible(lua_State* l) {
  int label = lua_tonumber(l, -1);
  lua_pop(l, 1);
  
  bool isVisible = lua_toboolean(l, -1);
  lua_pop(l, 1);
  
  handler<RendererScriptHandler>(l, "renderer")->setVisible(isVisible, label);
  return 0;
}

void RendererScriptHandler::setVisible(bool isVisible, int label) {
  view_->setVisible(isVisible, label);
}

int RendererScriptHandler::l_fadeInSwingCircle(lua_State* l) {
  int label = lua_tonumber(l, -1);
  lua_pop(l,1);

  handler<RendererScriptHandler>(l, "renderer")->fadeInSwingCircle(label);
  
  return 0;
}

void RendererScriptHandler::fadeInSwingCircle(int label) {
  view_->fadeInCircle(label);
}

int RendererScriptHandler::l_fadeOutSwingCircle(lua_State* l) {
  int label = lua_tonumber(l, -1);
  lua_pop(l,1);
  
  handler<RendererScriptHandler>(l, "renderer")->fadeOutSwingCircle(label);
  
  return 0;
}

void RendererScriptHandler::fadeOutSwingCircle(int label) {
  view_->fadeOutCircle(label);
}

int RendererScriptHandler::l_screenSize(lua_State* l) {
  return 0;
}
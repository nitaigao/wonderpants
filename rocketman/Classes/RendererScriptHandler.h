#ifndef RendererScriptHandler_H_
#define RendererScriptHandler_H_

#include "ScriptHandler.h"

class lua_State;
class IGameView;
class Component;

class String;
class AnimationCompleteHandler;

class RendererScriptHandler : public ScriptHandler {
  
public:
  
  RendererScriptHandler(lua_State* state, Component* component, IGameView* view);
  
private:
  
  static int l_playAnimation(lua_State* l);
  void playAnimation(const String& animationName, bool repeats, bool restoreLastFrame, AnimationCompleteHandler* callback);
  
private:
  
  static int l_shakeCamera(lua_State* l);
  void shakeCamera();

  
  static int l_removeVisible(lua_State* l);
  void removeVisible(int label);
  
  static int l_removeAnimable(lua_State* l);
  void removeAnimable(int label);

  
  static int l_fadeOut(lua_State* l);
  void fadeOut(float duration);
  
  static int l_fadeIn(lua_State* l);
  void fadeIn(float duration);
  
  static int l_fadeInSwingCircle(lua_State* l);
  void fadeInSwingCircle(int label);
  
  static int l_fadeOutSwingCircle(lua_State* l);
  void fadeOutSwingCircle(int label);

  static int l_continuousRotate(lua_State* l);
  static int l_follow(lua_State* l);
  
  static int l_flipX(lua_State* l);
  void flipX(int label);
  
  static int l_setVisible(lua_State* l);
  void setVisible(bool isVisible, int label);
  
  static int l_onScreen(lua_State* l);
  bool onScreen(int label);
  
  static int l_screenSize(lua_State* l);
  
  
private:
  
  IGameView* view_;
  Component* component_;
  
};

#endif

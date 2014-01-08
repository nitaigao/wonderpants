#include "AndroidPlatform.h"

#include "JniHelper.h"
#include "SString.h"
using namespace cocos2d;

String AndroidPlatform::appPath() {
  return "";
}

void AndroidPlatform::vibrate() {
  JniMethodInfo t;
  if (JniHelper::getStaticMethodInfo(t, "org/cocos2dx/lib/Cocos2dxActivity", "vibrate", "()V")) {
    t.env->CallStaticVoidMethod(t.classID, t.methodID);
    t.env->DeleteLocalRef(t.classID);
  }
}
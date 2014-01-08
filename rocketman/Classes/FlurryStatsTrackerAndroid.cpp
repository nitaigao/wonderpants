#include "FlurryStatsTrackerAndroid.h"

#include "Common.h"
#include "SaveState.h"

#include <jni.h>
#include <stdio.h>
#include <stdlib.h>


#include "JniHelper.h"
#include "android/jni/SystemInfoJni.h"
#include <android/log.h>
using namespace cocos2d;

void FlurryStatsTrackerAndroid::startSession() {
  
}

static void logEvent(const std::string& eventName, const std::map<std::string, std::string>& params) {
  JNIEnv* env = 0;
  
  JniHelper::getEnv(&env);
  
  jclass mapClass = env->FindClass("java/util/HashMap");  
  jsize map_len = 1;  
  jmethodID init = env->GetMethodID(mapClass, "<init>", "(I)V");
  jobject hashMap = env->NewObject(mapClass, init, map_len);
  
  jmethodID put = env->GetMethodID(mapClass, "put", "(Ljava/lang/Object;Ljava/lang/Object;)Ljava/lang/Object;");
  
  for (auto param : params) {
    jstring key = env->NewStringUTF(param.first.c_str());
    jstring value = env->NewStringUTF(param.second.c_str());
    env->CallObjectMethod(hashMap, put, key, value);
    env->DeleteLocalRef(key);
    env->DeleteLocalRef(value);    
  }
  
  jstring name = env->NewStringUTF(eventName.c_str());
  
  JniMethodInfo methodInfo;
  JniHelper::getStaticMethodInfo(methodInfo, "com/flurry/FlurryTracker", "logEvent", "(Ljava/lang/String;Ljava/util/Map;)V");
  methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID, name, hashMap);

  env->DeleteLocalRef(name); 
  env->DeleteLocalRef(hashMap);    
  env->DeleteLocalRef(mapClass);      
}

void FlurryStatsTrackerAndroid::winLevel(const SaveState& saveState) {  
  std::map<std::string, std::string> params;
  params["level"] = String::withFormat("%d", saveState.level()).c_str();
  params["chapter"] = String::withFormat("%d", saveState.chapter()).c_str();
  params["attempts"] = String::withFormat("%d", saveState.attempts()).c_str();
  params["coin"] = String::withFormat("%d", saveState.coins()).c_str();  
  logEvent("level_win", params);
}

void FlurryStatsTrackerAndroid::loseLevel(int level, int chapter) {
  std::map<std::string, std::string> params;
  params["level"] = String::withFormat("%d", level + 1).c_str();
  params["chapter"] = String::withFormat("%d", chapter + 1).c_str();
  logEvent("level_lose", params);
}
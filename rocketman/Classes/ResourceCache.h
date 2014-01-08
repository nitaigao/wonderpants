#ifndef ResourceCache_H_
#define ResourceCache_H_

class String;

#include "CCFileUtils.h"

class ResourceCache {
  
public:
  
  ~ResourceCache();
  
public:
  
  static ResourceCache* sharedCache();
  
  static void purgeCache();
  
public:
  
  String loadString(const char* path);
  
  cocos2d::CCFileData* loadBinary(const char* path);
    
private:
  
  std::map<String, String> stringCache_;
  std::map<String, cocos2d::CCFileData*> binaryCache_;
  
};

#endif

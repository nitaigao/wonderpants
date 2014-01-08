#ifndef PhysicsDataLoader_H_
#define PhysicsDataLoader_H_

class b2Body;
class String;

class PhysicsDataLoader {
  
public:
  
  void cache(const String& path);
  
  void loadBody(b2Body* body, const String& bodyKey);
  
};

#endif

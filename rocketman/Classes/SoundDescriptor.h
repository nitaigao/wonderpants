#ifndef SoundDescriptor_H_
#define SoundDescriptor_H_

#include "Common.h"

class SoundDescriptor {
  
public:
  
  inline void setGain(float gain) { gain_ = gain; };
  
  inline void addSound(const String& sound) { sounds_.push_back(sound); };
  
  String sound() const;
  
private:
  
  float gain_;
  std::vector<String> sounds_;
  
};

#endif

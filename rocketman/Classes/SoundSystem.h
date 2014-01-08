#ifndef SoundSystem_H_
#define SoundSystem_H_

#include "DefinedSounds.h"
#include "SoundDescriptor.h"
#include "Common.h"

class SoundSystem {
  
public:
  
  static SoundSystem* sharedSoundSystem();
  
  void init();
  
  void playMusic(const String& name);
  
  void playEffect(const String& name);
  
  void stopEffect(const String& name);
  
  void vibrate();
  
  void toggleMusic();
  
  void toggleSFX();
  
  void toggleVibrate();
  
  bool musicState();
  
  bool sfxState();
  
  bool vibrateState();
  
  void muteMusic();
  
  void unMuteMusic();
  
private:
  

  
private:
  
  String playingMusic_;
  
  std::map<String, SoundDescriptor> music_;
  std::map<String, SoundDescriptor> effects_;
  
  std::map<String, unsigned int> activeEffects_;
  
};

#endif

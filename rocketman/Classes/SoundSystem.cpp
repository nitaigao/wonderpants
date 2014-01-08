#include "SoundSystem.h"

#include "cocos2d.h"
#include "SimpleAudioEngine.h"
USING_NS_CC;

#include "Common.h"
#include "SoundDescriptor.h"
#include "Platform.h"

using namespace CocosDenshion;

#include "json.h"

static const char* MUSIC_STATE = "music_state";
static const char* SFX_STATE = "sfx_state";
static const char* VIBRATE_STATE = "sfx_state";

static const int MUSIC_VOLUME_MIN = 0;
static const int MUSIC_VOLUME_MAX = 1;

static SoundSystem* _sharedSoundSystem = 0;

SoundSystem* SoundSystem::sharedSoundSystem() {
  if (!_sharedSoundSystem) {
    _sharedSoundSystem = new SoundSystem();
  }
  return _sharedSoundSystem;
}

std::map<String, SoundDescriptor> load(const String& filename) {
  using namespace Json;
  const char* path = CCFileUtils::fullPathFromRelativePath(filename.c_str());
  String musicFile = String::fromFile(path);
  Reader reader;
  Value root;
  
  reader.parse(musicFile.str(), root);
  
  Value::Members members = root.getMemberNames();
  
  std::map<String, SoundDescriptor> sounds;
  
  for (std::string& member : members) {
    SoundDescriptor descriptor;
    
    double gain = root[member]["gain"].asDouble();
    descriptor.setGain(gain);
    
    Value effects = root[member]["files"];
    
    for (int i = 0; i < effects.size(); ++i) {
      String asset = root[member]["files"][i].asString();
      descriptor.addSound(asset);
    }
    
    sounds[member] = descriptor;
  }    
  return sounds;
}

void SoundSystem::init() {
  music_ = load("music.json");
  effects_ = load("sfx.json");  
  
  {
    bool isMusic = true;
    if (CCUserDefault::sharedUserDefault()->isKeyExist(MUSIC_STATE)) {
      isMusic = CCUserDefault::sharedUserDefault()->getBoolForKey(MUSIC_STATE);
    }
    SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(isMusic);
  }
  
  {
    bool isSFX = true;
    if (CCUserDefault::sharedUserDefault()->isKeyExist(SFX_STATE)) {
      isSFX = CCUserDefault::sharedUserDefault()->getBoolForKey(SFX_STATE);
    }
    SimpleAudioEngine::sharedEngine()->setEffectsVolume(isSFX);
  }
}

void SoundSystem::playMusic(const String& name) {
  if (playingMusic_ != name) {
    playingMusic_ = name;
    String file = music_[name].sound();
    String path = CCFileUtils::fullPathFromRelativePath(file.c_str());
    SimpleAudioEngine::sharedEngine()->playBackgroundMusic(path.c_str(), true);
  }
}

void SoundSystem::playEffect(const String& name) {
  if (effects_.find(name) != effects_.end()) {
    String file = effects_[name].sound();
    String path = CCFileUtils::fullPathFromRelativePath(file.c_str());
    unsigned int effectId = SimpleAudioEngine::sharedEngine()->playEffect(path.c_str());
    activeEffects_[name] = effectId;
    
  }
}

void SoundSystem::stopEffect(const String& name) {
  if (activeEffects_.find(name) != activeEffects_.end()) {
    unsigned int effectId = activeEffects_[name];
    SimpleAudioEngine::sharedEngine()->stopEffect(effectId);
  }
}

void SoundSystem::vibrate() {
  if (vibrateState()) {
    Platform::currentPlatform()->vibrate();
  }
}

bool toggle(const char* key) {
  bool state = CCUserDefault::sharedUserDefault()->getBoolForKey(key);
  float volume = state ? 0 : 1;
  CCUserDefault::sharedUserDefault()->setBoolForKey(key, !state);
  return volume;
}

bool state(const char* key) {
  if (!CCUserDefault::sharedUserDefault()->isKeyExist(key)) {
    CCUserDefault::sharedUserDefault()->setBoolForKey(key, true); 
  }
  return CCUserDefault::sharedUserDefault()->getBoolForKey(key);  
}

void SoundSystem::toggleMusic() {
  float volume = toggle(MUSIC_STATE);
  SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(volume);
}

void SoundSystem::toggleSFX() {
  float volume = toggle(SFX_STATE);
  SimpleAudioEngine::sharedEngine()->setEffectsVolume(volume);
}

void SoundSystem::toggleVibrate() {
  toggle(VIBRATE_STATE);
}

bool SoundSystem::musicState() {
  return state(MUSIC_STATE);
}

bool SoundSystem::sfxState() {
  return state(SFX_STATE);
}

bool SoundSystem::vibrateState() {
  return state(VIBRATE_STATE);
}

void SoundSystem::muteMusic() {
  SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(MUSIC_VOLUME_MIN);
}

void SoundSystem::unMuteMusic() {
  SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(MUSIC_VOLUME_MAX);
}
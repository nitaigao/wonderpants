#include "SoundEffectLoadTask.h"

#include "SimpleAudioEngine.h"
using namespace CocosDenshion;

SoundEffectLoadTask::SoundEffectLoadTask(const String& effectFile) : effectFile_(effectFile) {
  
}

void SoundEffectLoadTask::execute() {
  SimpleAudioEngine::sharedEngine()->preloadEffect(effectFile_.c_str());
}

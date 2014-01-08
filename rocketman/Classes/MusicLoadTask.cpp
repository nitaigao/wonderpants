#include "MusicLoadTask.h"

#include "SimpleAudioEngine.h"
using namespace CocosDenshion;

MusicLoadTask::MusicLoadTask(const String& musicFile) : musicFile_(musicFile) {
  
}

void MusicLoadTask::execute() {
  SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic(musicFile_.c_str());
}

#include "IOSPlatform.h"

#include "String.h"

#include <Foundation/Foundation.h>
#include <AudioToolbox/AudioToolbox.h>

String IOSPlatform::appPath() {
  return [[[NSBundle mainBundle] bundlePath] cStringUsingEncoding:NSUTF8StringEncoding];
}

void IOSPlatform::vibrate() {
  AudioServicesPlaySystemSound(kSystemSoundID_Vibrate);
}
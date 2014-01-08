#include "AppDelegate.h"

#include "cocos2d.h"
USING_NS_CC;

#include "SimpleAudioEngine.h"
using namespace CocosDenshion;

#include "StatsTracker.h"
#include "Game.h"

AppDelegate::AppDelegate() {
  game = new Game();
}

AppDelegate::~AppDelegate() {
  delete  game;
}

bool AppDelegate::initInstance() {
  return true;
}

bool AppDelegate::applicationDidFinishLaunching()
{ 
	// initialize director
	CCDirector *pDirector = CCDirector::sharedDirector();
  pDirector->setOpenGLView(&CCEGLView::sharedOpenGLView());
  
//  pDirector->setDisplayFPS(true);
  
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
  
	// sets landscape mode
  pDirector->setDeviceOrientation(kCCDeviceOrientationLandscapeLeft);
  
#endif 
  
  pDirector->setDepthTest(false); // stops z fighting on ios
  
  const char* key = "SCREEN_ORIENTATION";
  ccDeviceOrientation orientation = (ccDeviceOrientation)CCUserDefault::sharedUserDefault()->getIntegerForKey(key);  
  if (orientation != kCCDeviceOrientationLandscapeLeft && orientation != kCCDeviceOrientationLandscapeRight) {
    orientation = kCCDeviceOrientationLandscapeLeft;
    CCUserDefault::sharedUserDefault()->setIntegerForKey(key, orientation);
  }
  pDirector->setDeviceOrientation(kCCDeviceOrientationPortrait);
    
  game->run();
  
	return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground()
{
  CCDirector::sharedDirector()->pause();

	// if you use SimpleAudioEngine, it must be pause
  SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
  
  
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground()
{
    CCDirector::sharedDirector()->resume();
	
	// if you use SimpleAudioEngine, it must resume here
  SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
}

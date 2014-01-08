#import <UIKit/UIKit.h>
#import "AppController.h"
#import "cocos2d.h"
#import "EAGLView.h"
#import "AppDelegate.h"

#import "RootViewController.h"
#include "CacheMaster.h"

#import "UIDevice-Hardware.h"

#import "StatsTracker.h"
#import "iRate.h"
#import "SaveMigrator.h"

@implementation UIScreen(Private)

- (CGRect) bounds {
  return CGRectMake(0, 0, 320, 480);
}


@end

@implementation AppController

static AppDelegate s_sharedApplication;

+ (void)initialize {
#ifdef RESET_PREFS 
  NSString *appDomain = [[NSBundle mainBundle] bundleIdentifier];
  [[NSUserDefaults standardUserDefaults] removePersistentDomainForName:appDomain]; 
#endif
  
  [iRate sharedInstance].appStoreID = [[[NSBundle mainBundle] objectForInfoDictionaryKey:@"SCRStoreId"] integerValue];
  [iRate sharedInstance].applicationName = @"Wonder Pants";
  [iRate sharedInstance].message = @"Enjoying Wonder Pants?\nHow about a 5 star review?";
  [iRate sharedInstance].daysUntilPrompt = 0;
  [iRate sharedInstance].eventsUntilPrompt = 39;
}

- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions {        
  
  [[SaveMigrator migrator] migrate:@"full_level_data.xml"];
  
  window = [[UIWindow alloc] initWithFrame: [[UIScreen mainScreen] bounds]];
  EAGLView *__glView = [EAGLView viewWithFrame: [window bounds]
                                   pixelFormat: kEAGLColorFormatRGBA8
                                   depthFormat: GL_DEPTH_COMPONENT16_OES
                            preserveBackbuffer: NO
                                    sharegroup: nil
                                 multiSampling: NO
                               numberOfSamples: 0 ];
  
  viewController = [[RootViewController alloc] initWithNibName:nil bundle:nil];
  viewController.wantsFullScreenLayout = YES;
  viewController.view = __glView;

  window.rootViewController = viewController;
  [window makeKeyAndVisible];

  [[UIApplication sharedApplication] setStatusBarHidden: YES];
  
#ifdef __IPHONE_OS_VERSION_MAX_ALLOWED
  bool allowRetina = true;
  
  // disable retina on iPod due to memory requirements
  if([[[UIDevice currentDevice] platformString] rangeOfString:@"iPod"].location != NSNotFound) {
    allowRetina = false;
  }
  
  cocos2d::CCDirector::sharedDirector()->enableRetinaDisplay(allowRetina);
#endif

  StatsTracker().startSession();
  cocos2d::CCApplication::sharedApplication().run();

  return YES;
}


- (void)applicationWillResignActive:(UIApplication *)application {
  /*
   Sent when the application is about to move from active to inactive state. This can occur for certain types of temporary interruptions (such as an incoming phone call or SMS message) or when the user quits the application and it begins the transition to the background state.
   Use this method to pause ongoing tasks, disable timers, and throttle down OpenGL ES frame rates. Games should use this method to pause the game.
   */
	cocos2d::CCDirector::sharedDirector()->pause();
}

- (void)applicationDidBecomeActive:(UIApplication *)application {
  /*
   Restart any tasks that were paused (or not yet started) while the application was inactive. If the application was previously in the background, optionally refresh the user interface.
   */
	cocos2d::CCDirector::sharedDirector()->resume();
}

- (void)applicationDidEnterBackground:(UIApplication *)application {
  /*
   Use this method to release shared resources, save user data, invalidate timers, and store enough application state information to restore your application to its current state in case it is terminated later. 
   If your application supports background execution, called instead of applicationWillTerminate: when the user quits.
   */
	cocos2d::CCDirector::sharedDirector()->stopAnimation();
}

- (void)applicationWillEnterForeground:(UIApplication *)application {
  /*
   Called as part of  transition from the background to the inactive state: here you can undo many of the changes made on entering the background.
   */
	cocos2d::CCDirector::sharedDirector()->startAnimation();
}

- (void)applicationWillTerminate:(UIApplication *)application {
  /*
   Called when the application is about to terminate.
   See also applicationDidEnterBackground:.
   */
}

- (void)applicationDidReceiveMemoryWarning:(UIApplication *)application {
  NSLog(@"############## MEMORY WARNING #################");
  CacheMaster::purgeTemporaryCaches();
}

@end


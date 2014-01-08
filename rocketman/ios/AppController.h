//
//  rocketmanAppController.h
//  rocketman
//
//  Created by Nicholas Kostelnik on 17/11/2011.
//  Copyright Black Art Studios 2011. All rights reserved.
//

@class RootViewController;

@interface AppController : NSObject <UIAccelerometerDelegate, UIAlertViewDelegate, UITextFieldDelegate,UIApplicationDelegate> {
    UIWindow *window;
    RootViewController	*viewController;
}

@end


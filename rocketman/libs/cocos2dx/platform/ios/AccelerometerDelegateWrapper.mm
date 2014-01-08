/****************************************************************************
 Copyright (c) 2010 cocos2d-x.org
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#import "AccelerometerDelegateWrapper.h"

@implementation AccelerometerDispatcher

static AccelerometerDispatcher* s_pAccelerometerDispatcher;

@synthesize acceleration_;

+ (id) sharedAccelerometerDispather
{
    if (s_pAccelerometerDispatcher == nil) {
        s_pAccelerometerDispatcher = [[self alloc] init];
    }
    
    return s_pAccelerometerDispatcher;
}

- (id) init
{
    acceleration_ = new cocos2d::CCAcceleration();

    [[UIAccelerometer sharedAccelerometer] setDelegate:self];
    [[UIAccelerometer sharedAccelerometer] setUpdateInterval:1.0f/20.0f];

    return self;
}

- (void) dealloc
{
    [[UIAccelerometer sharedAccelerometer] setDelegate:nil];
    s_pAccelerometerDispatcher = 0;
    delete acceleration_;
    [super dealloc];
}

- (void) addDelegate: (cocos2d::CCAccelerometerDelegate *) delegate
{
    for (std::vector<cocos2d::CCAccelerometerDelegate*>::iterator i = delegates_.begin(); i != delegates_.end(); ++i) {
      if(delegate == (*i)) {
        return;
      }
    }
    
    delegates_.push_back(delegate);
}

- (void) removeDelegate: (cocos2d::CCAccelerometerDelegate *) delegate {
    for (std::vector<cocos2d::CCAccelerometerDelegate*>::iterator i = delegates_.begin(); i != delegates_.end();) {
      if ((*i) == delegate) {
        i = delegates_.erase(i);
      } else {
        ++i;
      }
    }
}

- (void)accelerometer:(UIAccelerometer *)accelerometer didAccelerate:(UIAcceleration *)acceleration
{
    acceleration_->x = acceleration.x;
    acceleration_->y = acceleration.y;
    acceleration_->z = acceleration.z;
    acceleration_->timestamp = acceleration.timestamp;
    
    double tmp = acceleration_->x;
    
    switch ([[UIApplication sharedApplication] statusBarOrientation]) 
    {
    case UIInterfaceOrientationLandscapeRight:
        acceleration_->x = -acceleration_->y;
        acceleration_->y = tmp;
        break;
        
    case UIInterfaceOrientationLandscapeLeft:
        acceleration_->x = acceleration_->y;
        acceleration_->y = -tmp;
        break;
        
    case UIInterfaceOrientationPortraitUpsideDown:
        acceleration_->x = -acceleration_->y;
        acceleration_->y = -tmp;
        break;
            
    case UIInterfaceOrientationPortrait:
        break;
    }

    for (std::vector<cocos2d::CCAccelerometerDelegate*>::iterator i = delegates_.begin(); i != delegates_.end(); ++i) {
      (*i)->didAccelerate(acceleration_);
    }
}

@end


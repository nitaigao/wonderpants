#include "FlurryStatsTrackerIOS.h"

#import "FlurryAnalytics.h"

#include "Common.h"
#include "SaveState.h"

#import "iRate.h"

void FlurryStatsTrackerIOS::startSession() {
  [FlurryAnalytics startSession:@"LA63AT6QBPQRMNUIAD81"];
}

void FlurryStatsTrackerIOS::winLevel(const SaveState& saveState) {
  NSDictionary* params = [NSDictionary dictionaryWithObjectsAndKeys:
                          [NSNumber numberWithInt:saveState.level()], @"level",
                          [NSNumber numberWithInt:saveState.chapter()], @"chapter",
                          [NSNumber numberWithInt:saveState.attempts()], @"attempts",
                          [NSNumber numberWithInt:saveState.coins()], @"coin", nil];
  [FlurryAnalytics logEvent:@"level_win" withParameters:params];
  [[iRate sharedInstance] logEvent:NO];
}

void FlurryStatsTrackerIOS::loseLevel(int level, int chapter) {
  NSDictionary* params = [NSDictionary dictionaryWithObjectsAndKeys:
                          [NSNumber numberWithInt:level + 1], @"level",
                          [NSNumber numberWithInt:chapter + 1], @"chapter", nil];
  
  [FlurryAnalytics logEvent:@"level_lose" withParameters:params];
}
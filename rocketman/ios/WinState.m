
#import "WinState.h"

@implementation WinState

@synthesize collectables, level, chapter, time, stylePoints, attempts;

@dynamic score, rating;

+ (id)state {
  return [[[self alloc] init] autorelease];
}

+ (id)stateForLevel:(NSInteger)level chapter:(NSInteger)chapter bonus:(NSInteger)bonus collectables:(NSInteger)collectables time:(NSTimeInterval)time attempts:(NSInteger)attempts {
  WinState* state = [[self alloc] initWithLevel:level chapter:chapter];
  state.stylePoints = bonus;
  state.collectables = collectables;
  state.time = time;
  state.attempts = attempts;
  return [state autorelease];
}

+ (id)defaultStateForLevel:(NSInteger)level chapter:(NSInteger)chapter {
  return [[[self alloc] initWithLevel:level chapter:chapter] autorelease];
}

+ (id)fullWinStateForLevel:(NSInteger)level chapter:(NSInteger)chapter {
  WinState* state = [[[self alloc] initWithLevel:level chapter:chapter] autorelease];
  state.collectables = 3;
  state.time = 0;
  return state;
}

- (id)initWithLevel:(NSInteger)aLevel chapter:(NSInteger)aChapter {
  self = [super init];
  if (self) {
    level = aLevel;
    chapter = aChapter;
    time = 0;
    collectables = 0;
    stylePoints = 0;
  }
  return self;
}

- (void)encodeWithCoder:(NSCoder *)aCoder {
  [aCoder encodeInteger:collectables forKey:@"collectables"];
  [aCoder encodeDouble:time forKey:@"time"];
  [aCoder encodeInteger:stylePoints forKey:@"style"];
  [aCoder encodeInteger:level forKey:@"level"];
  [aCoder encodeInteger:chapter forKey:@"chapter"];
}

- (id)initWithCoder:(NSCoder *)coder {
  self = [super init];
  if (self) {
    collectables = [coder decodeIntegerForKey:@"collectables"];
    time = [coder decodeDoubleForKey:@"time"];
    level = [coder decodeIntegerForKey:@"level"];
    chapter = [coder decodeIntegerForKey:@"chapter"];
    stylePoints = [coder decodeIntegerForKey:@"style"];
  }
  return self;
}

- (void)update:(WinState*)state {
  if (state.collectables > self.collectables) {
    collectables = state.collectables;
  }
  if (state.time > self.time) {
    time = state.time;
  }
  if (state.stylePoints > self.stylePoints) {
    stylePoints = state.stylePoints;
  }
}

- (NSInteger)score {
  NSInteger collectableScore = collectables * 1000;
  NSInteger timeScore = !time ? 0 : 2000.0f / time;
  NSInteger styleScore = stylePoints;
  return collectableScore + timeScore + styleScore;
}

- (NSInteger)rating {
  if (self.score > 7000) {
    return 3;
  }
  
  if (self.score > 5000) {
    return 2;
  }
  
  if (self.score > 2000) {
    return 1;
  }
  
  return 0;
}

@end

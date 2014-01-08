
#import <Foundation/Foundation.h>

@interface WinState : NSObject<NSCoding> {
  NSInteger collectables;
  NSInteger level;
  NSInteger chapter;
  NSInteger stylePoints;
  NSTimeInterval time;
  NSInteger attempts;
}


@property (nonatomic, readonly) NSInteger chapter;
@property (nonatomic, readonly) NSInteger level;

@property (nonatomic, readonly) NSInteger score;
@property (nonatomic, readonly) NSInteger rating;

@property (nonatomic, readwrite) NSInteger collectables;
@property (nonatomic, readwrite) NSTimeInterval time;
@property (nonatomic, readwrite) NSInteger stylePoints;
@property (nonatomic, readwrite) NSInteger attempts;


+ (id)stateForLevel:(NSInteger)level chapter:(NSInteger)chapter bonus:(NSInteger)bonus collectables:(NSInteger)collectables time:(NSTimeInterval)time attempts:(NSInteger)attempts;
+ (id)defaultStateForLevel:(NSInteger)level chapter:(NSInteger)chapter;
+ (id)fullWinStateForLevel:(NSInteger)level chapter:(NSInteger)chapter;

- (id)initWithLevel:(NSInteger)aLevel chapter:(NSInteger)aChapter;
- (void)update:(WinState*)state;
@end

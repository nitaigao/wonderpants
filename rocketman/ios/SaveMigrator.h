#import <Foundation/Foundation.h>

@interface SaveMigrator : NSObject

+ (id)migrator;
- (void)migrate:(NSString*)path;

@end

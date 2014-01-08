#import "SaveMigrator.h"

#import "WinState.h"
#include "SaveGame.h"
#include "SaveState.h"

@implementation SaveMigrator

+ (NSString*)documents {
  NSArray* paths = NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES);
  return [paths objectAtIndex:0];
}

+ (id)migrator {
  return [[[SaveMigrator alloc] init] autorelease];
}

- (void)migrate:(NSString*)path {
  NSString* fullPath = [[SaveMigrator documents] stringByAppendingPathComponent:path];
  if ([[NSFileManager defaultManager] fileExistsAtPath:fullPath]) {
    NSMutableArray* levelData = [NSKeyedUnarchiver unarchiveObjectWithFile:fullPath];
    
    for (WinState* oldWinstate in levelData) {
      SaveState newWinState(oldWinstate.chapter, oldWinstate.level, oldWinstate.collectables, oldWinstate.stylePoints, oldWinstate.attempts, oldWinstate.time);
      SaveGame::sharedSaveData()->saveProgress(newWinState);
    }
    SaveGame::sharedSaveData()->commit();
    [[NSFileManager defaultManager] removeItemAtPath:fullPath error:0];
  }
}

@end

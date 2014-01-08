#include "StatsTracker.h"

#include "Common.h"

#include "FlurryStatsTrackerIOS.h"
#include "FlurryStatsTrackerAndroid.h"
#include "DefaultStatsStore.h"

StatsTracker::~StatsTracker() {
  SAFE_DELETE(dataStore_);
}

StatsTracker::StatsTracker() {
#if defined(__IPHONE_OS_VERSION_MAX_ALLOWED) && defined(NDEBUG)
  dataStore_ = new FlurryStatsTrackerIOS();
#elif defined(__ANDROID__)
  dataStore_ = new FlurryStatsTrackerAndroid();
#else
  dataStore_ = new DefaultStatsStore();
#endif
}

void StatsTracker::startSession() {
  dataStore_->startSession();
}

void StatsTracker::winLevel(const SaveState& saveState) {
  dataStore_->winLevel(saveState);
}

void StatsTracker::loseLevel(int level, int chapter) {
  dataStore_->loseLevel(level, chapter);
}
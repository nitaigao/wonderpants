#include "ChapterData.h"

#include "Common.h"

#include "CCFileUtils.h"
USING_NS_CC;

#include "ResourceCache.h"

#include "json.h"
#include "GameConfig.h"

using namespace Json;

ChapterData ChapterData::forChapter(int chapter) {
  return ChapterData::fromFile(GameConfig::chaptersFile()).objectAtIndex(chapter);
}

Array<ChapterData> ChapterData::fromFile(const String& filepath) {
  String data = ResourceCache::sharedCache()->loadString(filepath.c_str());
  
  Reader reader;
  Value root;
  
  reader.parse(data.str(), root);
  
  std::vector<ChapterData> chapters;
  
  for (int i = 0; i < root.size(); ++i) {
    ChapterData chapterData(root[i]["comic"].asString(),
                            root[i]["comic_down"].asString(),
                            root[i]["stacks"].asString(),
                            root[i]["background"].asString(),
                            root[i]["level_end"].asString(),
                            root[i]["required"].asInt(),
                            root[i]["intro"].asString(),
                            root[i]["levels"].asInt(),
                            i);
    
    chapters.push_back(chapterData);
  }
  
  return chapters;
}

ChapterData::ChapterData(const String& comic, const String& comicDown, 
                         const String& stacks, const String& background,
                         const String& levelEnd, int required,
                         const String& intro, int levels, int chapter) 
  : comic_(comic)
  , comicDown_(comicDown)
  , stacks_(stacks)
  , background_(background)
  , levelEnd_(levelEnd)
  , required_(required)
  , intro_(intro)
  , levels_(levels)
  , chapter_(chapter) {  
}

Array<ChapterData> ChapterData::chapters() {
  return ChapterData::fromFile(GameConfig::chaptersFile());
}

int ChapterData::totalLevelCount() {
  Array<ChapterData> chaptersData = ChapterData::fromFile(GameConfig::chaptersFile());
  
  int levelCount = 0;
  for (ChapterData chapterData : chaptersData) {
    levelCount += chapterData.levels();
  }
  
  return levelCount;  
}

int ChapterData::totalChapterCount() {
  return ChapterData::fromFile(GameConfig::chaptersFile()).count();  
}

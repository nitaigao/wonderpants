#ifndef ChapterData_H_
#define ChapterData_H_

#include "Common.h"

class ChapterData {
  
public:
  
  static Array<ChapterData> chapters();
  
  static Array<ChapterData> fromFile(const String& filepath);
  
  static ChapterData forChapter(int chapter);
  
  static int totalLevelCount();
  
  static int totalChapterCount();
  
public:
    
  PROPERTY_READONLY(String, comic);
  PROPERTY_READONLY(String, comicDown);
  PROPERTY_READONLY(String, stacks);
  PROPERTY_READONLY(String, background);
  PROPERTY_READONLY(String, levelEnd);
  PROPERTY_READONLY(int, required);
  PROPERTY_READONLY(String, intro);
  PROPERTY_READONLY(int, levels);
  PROPERTY_READONLY(int, chapter);
  
private:
  
  ChapterData(const String& comic, 
              const String& comic_down, 
              const String& stacks, 
              const String& background,
              const String& levelEnd,
              int required,
              const String& intro,
              int levels,
              int chapter);

};

#endif

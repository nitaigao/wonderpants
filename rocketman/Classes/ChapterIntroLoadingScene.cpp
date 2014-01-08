#include "ChapterIntroLoadingScene.h"

#include "ScreenManager.h"
#include "SpriteLoadTask.h"
#include "MusicLoadTask.h"
#include "SpriteSheetLoadTask.h"

ChapterIntroLoadingScene* ChapterIntroLoadingScene::nodeWithChapter(int chapter) {
  ChapterIntroLoadingScene* scene = new ChapterIntroLoadingScene(chapter);
  scene->init();
  scene->autorelease();
  return scene;
}

ChapterIntroLoadingScene::ChapterIntroLoadingScene(int chapter) : chapter_(chapter) {
  
}

void ChapterIntroLoadingScene::setupTasks() {
  String spriteSheet = String::withFormat("chapter%d_intro.plist", chapter_ + 1); // data is zero indexed, assets are not
  loadTasks_.push(new SpriteSheetLoadTask(spriteSheet));
  loadTasks_.push(new MusicLoadTask("kh_music_story_01.mp3"));
  loadTasks_.push(new SpriteSheetLoadTask("fonts.plist"));
}

void ChapterIntroLoadingScene::changeScene() {
  ScreenManager::activateChapterIntroScreen(chapter_);
}

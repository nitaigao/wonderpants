#include "ChaptersScene.h"

#include "cocos2d.h"
USING_NS_CC;

#include "ChaptersSceneView.h"
#include "ChapterData.h"

#include "ChapterView.h"
#include "BackButton.h"

#include "ScreenManager.h"
#include "SoundSystem.h"
#include "SaveGame.h"

#include "GameConfig.h"
#include "CCScrollLayer.h"

static const int TAG_CHAPTERS = 100;

ChaptersScene* ChaptersScene::nodeWithChapter(int chapter) {
  ChaptersScene* scene = new ChaptersScene();
  scene->initWithChapter(chapter);
  scene->autorelease();
  return scene;
}

void ChaptersScene::initWithChapter(int chapter) {
  {
    ChaptersSceneView* view = ChaptersSceneView::nodeWithController(this);
    this->addChild(view, 0, TAG_CHAPTERS);
    
    Array<ChapterData> chapters = ChapterData::fromFile("chapters.json");

    int coins = SaveGame::sharedSaveData()->totalCoins();

    int index = 0;
    for (ChapterData chapterData : chapters) {
      int score = SaveGame::sharedSaveData()->chapterScore(index);
      ChapterView* chapterView = ChapterView::viewWithData(chapterData, score, coins, this);
      view->addChapterView(chapterView);
      index++;
    }
    
    view->setChapter(chapter+1);
    view->setCoins(SaveGame::sharedSaveData()->totalCoins());
  }

  {
    BackButton* back = BackButton::itemWithController(this, menu_selector(ChaptersScene::back));
    this->addChild(back);
  }
}

bool ChaptersScene::init() {
  return true;
}

void ChaptersScene::back(cocos2d::CCObject* sender) {
  ScreenManager::activateTitleScreen();
}

void ChaptersScene::selectChapter(cocos2d::CCObject* sender) {
  SoundSystem::sharedSoundSystem()->playEffect("menu_click");  
  int chapter = static_cast<CCMenuItem*>(sender)->getTag();

  if (!SaveGame::sharedSaveData()->completedLevels(chapter)) {
    ScreenManager::loadAndDisplayChapterIntroScreen(chapter);
  } else {
    ScreenManager::activateLevelsScreen(chapter); 
  };
}

void ChaptersScene::pageChanged(cocos2d::CCObject* sender) {
  CCScrollLayer* scrollLayer = static_cast<CCScrollLayer*>(sender);
  int page = scrollLayer->getPage();
  SoundSystem::sharedSoundSystem()->playEffect("comic_move");
  static_cast<ChaptersSceneView*>(getChildByTag(TAG_CHAPTERS))->bounceComic(page);
}

void ChaptersScene::scrollToChapter(int chapter) {
  static_cast<ChaptersSceneView*>(getChildByTag(TAG_CHAPTERS))->selectChapter(chapter); 
}
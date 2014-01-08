#include "ChapterIntroSceneView.h"

#include "Common.h"
#include "ChapterData.h"

#include "cocos2d.h"
USING_NS_CC;

#include "ChapterIntroScene.h"
#include "SoundSystem.h"

#include "CClabelBNFont.h"

static int SLIDE_SECS = 1;
static float WAIT_SECS = 2;

ChapterIntroSceneView* ChapterIntroSceneView::nodeWithController(ChapterIntroScene* controller, int chapter) {
  ChapterIntroSceneView* view = new ChapterIntroSceneView();
  view->initWithController(controller, chapter);
  view->autorelease();
  return view;
}

void ChapterIntroSceneView::initWithController(ChapterIntroScene* controller, int chapter) {
  String comic = ChapterData::forChapter(chapter).intro();
  CCSprite* comicSprite = CCSprite::spriteWithSpriteFrameName(comic.c_str());
  comicSprite->setScale(1.11);
  comicSprite->setPosition(ccp(400, -220));
  addChild(comicSprite);
  
  CCFiniteTimeAction* comicSequence = CCSequence::actions
  (
   CCDelayTime::actionWithDuration(1.5),
   CCMoveTo::actionWithDuration(SLIDE_SECS, ccp(75, -220)),
   CCDelayTime::actionWithDuration(WAIT_SECS),
   CCMoveTo::actionWithDuration(SLIDE_SECS, ccp(400, 25)),
   CCDelayTime::actionWithDuration(WAIT_SECS),
   CCMoveTo::actionWithDuration(SLIDE_SECS, ccp(75, 40)),
   CCDelayTime::actionWithDuration(WAIT_SECS),
   CCMoveTo::actionWithDuration(SLIDE_SECS, ccp(400, 295)),
   CCDelayTime::actionWithDuration(WAIT_SECS),
   CCMoveTo::actionWithDuration(SLIDE_SECS, ccp(75, 295)),
   CCDelayTime::actionWithDuration(WAIT_SECS),
   CCMoveTo::actionWithDuration(SLIDE_SECS, ccp(400, 565)),
   CCDelayTime::actionWithDuration(WAIT_SECS),
   CCMoveTo::actionWithDuration(SLIDE_SECS, ccp(75, 565)),
   CCDelayTime::actionWithDuration(2),   
   CCCallFuncN::actionWithTarget(controller, callfuncN_selector(ChapterIntroScene::continueToGame)), 0
  );
  
  if (chapter == 0) {
    comicSprite->setScale(1.4);
    comicSprite->setPosition(ccp(400, -380));
    float WAIT_SECS = 1.78;
    
    comicSequence = CCSequence::actions
    (
     CCDelayTime::actionWithDuration(1.5),
     CCMoveTo::actionWithDuration(SLIDE_SECS, ccp(75, -380)),
     CCDelayTime::actionWithDuration(WAIT_SECS),
     CCMoveTo::actionWithDuration(SLIDE_SECS, ccp(400, -105)),
     CCDelayTime::actionWithDuration(WAIT_SECS),
     CCMoveTo::actionWithDuration(SLIDE_SECS, ccp(75, -90)),
     CCDelayTime::actionWithDuration(WAIT_SECS),
     CCMoveTo::actionWithDuration(SLIDE_SECS, ccp(400, 160)),
     CCDelayTime::actionWithDuration(WAIT_SECS),
     CCMoveTo::actionWithDuration(SLIDE_SECS, ccp(75, 160)),
     CCDelayTime::actionWithDuration(WAIT_SECS),
     CCMoveTo::actionWithDuration(SLIDE_SECS, ccp(400, 425)),
     CCDelayTime::actionWithDuration(WAIT_SECS),
     CCMoveTo::actionWithDuration(SLIDE_SECS, ccp(75, 425)),
     CCDelayTime::actionWithDuration(WAIT_SECS),
     CCMoveTo::actionWithDuration(SLIDE_SECS, ccp(400, 700)),
     CCDelayTime::actionWithDuration(WAIT_SECS),
     CCMoveTo::actionWithDuration(SLIDE_SECS, ccp(75, 700)),
     CCDelayTime::actionWithDuration(0.5),   
     CCCallFuncN::actionWithTarget(controller, callfuncN_selector(ChapterIntroScene::continueToGame)),
     0
     );
  }

  
  comicSprite->runAction(comicSequence);
  SoundSystem::sharedSoundSystem()->playMusic("chapter_intro");
  
  CCSize screenSize = CCDirector::sharedDirector()->getWinSize();
  
  CCLabelBNFont* continueMessage = CCLabelBNFont::labelWithString("tap to skip", "soupofjustice_18_white.fnt");
  continueMessage->setOpacity(0);
  continueMessage->setPosition(ccp(screenSize.width - (screenSize.width / 7), screenSize.height/15));
  addChild(continueMessage);
  
  float flashInterval = 0.5f;
  CCFiniteTimeAction* continueFlashSequence = CCSequence::actions
  (
   CCFadeIn::actionWithDuration(flashInterval),
   CCFadeOut::actionWithDuration(flashInterval),
   0
  );
  CCRepeatForever* flashRepeat = CCRepeatForever::actionWithAction(static_cast<CCActionInterval*>(continueFlashSequence));
  continueMessage->runAction(flashRepeat);
}
 

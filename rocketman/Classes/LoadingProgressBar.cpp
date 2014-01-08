#include "LoadingProgressBar.h"

#include "SpriteSheetLoadTask.h"

USING_NS_CC;

static const int TAG_PROGRESS = 1;

LoadingProgressBar* LoadingProgressBar::node() {
  LoadingProgressBar* node = new LoadingProgressBar();
  node->init();
  node->autorelease();
  return node;
}

bool LoadingProgressBar::init() {
  CCSize screenSize = CCDirector::sharedDirector()->getWinSize();

  CCSprite* loadingWhite = CCSprite::spriteWithFile("loading_white.png");
  this->addChild(loadingWhite);
  
  return true;
}

void LoadingProgressBar::setProgress(float progress) {
  removeChildByTag(TAG_PROGRESS, true);
  CCSprite* progressSprite = createProgress(progress);
  addChild(progressSprite, progressSprite->getZOrder(), TAG_PROGRESS);
}

CCSprite* LoadingProgressBar::createProgress(float progress) {
  CCSprite* progressTexture = CCSprite::spriteWithFile("loading_red.png");
  progressTexture->setBlendFunc({GL_DST_ALPHA, GL_ZERO});
  
  CCSprite* progressMask = CCSprite::spriteWithFile("loading_red.png");
  progressMask->setPosition(ccp(-109 + (210*progress), 28));
  progressMask->setBlendFunc({GL_ONE, GL_ZERO});
  
  CCRenderTexture* progressRT = CCRenderTexture::renderTextureWithWidthAndHeight(progressTexture->getContentSizeInPixels().width, 
                                                                                 progressTexture->getContentSizeInPixels().height);
  
  progressRT->begin();
  progressMask->visit();
  progressTexture->draw();
  progressRT->end();
  
  CCSprite* progressSprite = CCSprite::spriteWithTexture(progressRT->getSprite()->getTexture());
  progressSprite->setFlipY(true);
  
  if (CC_CONTENT_SCALE_FACTOR() == 1) {
    progressSprite->setPosition(ccp(0, 0)); 
  }
  
  if (CC_CONTENT_SCALE_FACTOR() == 2) {
    progressSprite->setPosition(ccp(101, 27));
  }
  
  return progressSprite;
}
#include "TitleLoadList.h"

#include "SoundEffectLoadTask.h"
#include "SpriteSheetLoadTask.h"
#include "MusicLoadTask.h"
#include "ILoadTask.h"

void TitleLoadList::fillLoadList(std::queue<ILoadTask *>& loadTasks) {
  loadTasks.push(new SpriteSheetLoadTask("country_backgrounds.plist"));
  loadTasks.push(new SpriteSheetLoadTask("city_backgrounds.plist"));
  loadTasks.push(new SpriteSheetLoadTask("jungle_backgrounds.plist"));
  
  loadTasks.push(new SpriteSheetLoadTask("ui_backgrounds.plist"));
  loadTasks.push(new SpriteSheetLoadTask("transition.plist"));
  loadTasks.push(new SpriteSheetLoadTask("chapter_comics.plist"));

  //TODO: The 7th sheet to be loaded fails in cocos
  loadTasks.push(new SpriteSheetLoadTask("dummy.plist"));
  
  loadTasks.push(new SpriteSheetLoadTask("fonts.plist"));
  loadTasks.push(new SpriteSheetLoadTask("chapters.plist"));
  loadTasks.push(new SpriteSheetLoadTask("ui.plist"));
  
  loadTasks.push(new MusicLoadTask("kh_music_title_loop_01.mp3"));
  
  loadTasks.push(new SoundEffectLoadTask("kh_music_ident_04.mp3"));
  loadTasks.push(new SoundEffectLoadTask("kh_sfx_menu_sweep_01.mp3"));
  loadTasks.push(new SoundEffectLoadTask("kh_sfx_menu_sweep_02.mp3"));
  loadTasks.push(new SoundEffectLoadTask("kh_sfx_menu_sweep_03.mp3"));
  loadTasks.push(new SoundEffectLoadTask("kh_sfx_menu_sweep_04.mp3"));
  loadTasks.push(new SoundEffectLoadTask("kh_sfx_menu_sweep_05.mp3"));
  loadTasks.push(new SoundEffectLoadTask("kh_sfx_menu_sweep_06.mp3"));
  loadTasks.push(new SoundEffectLoadTask("kh_sfx_menu_sweep_07.mp3"));
  loadTasks.push(new SoundEffectLoadTask("kh_sfx_menu_sweep_08.mp3"));
}
#include "ScriptManager.h"

#include "Common.h"
#include "Component.h"
#include "Level.h"
#include "LuaState.h"
#include "StateCache.h"
#include "GameState.h"

#include "cocos2d.h"
USING_NS_CC;

#include "Input.h"
#include "EventSystem.h"
#include "Macros.h"

#include "AttributeScriptHandler.h"

static const String SCRIPT_TYPE = "script";
static const String SCRIPT_KEY_SCRIPT = "script";

EntityManager* ScriptManager::clone() {
  return new ScriptManager();
}

ScriptManager::~ScriptManager() {
  for (LuaState* state : states_) {
    SAFE_DELETE(state);
  }
}

void setGlobals(LuaState* state, std::map<String, Value> attrs) {
  for (auto attr : attrs) {
    state->setGlobal(attr.first, attr.second);
  }
}

void ScriptManager::setup(Level* level, IGameView* view, IGameUI* ui, Physics* physics, EventSystem* eventSystem, PlayerState* playerState) {
  level_ = level;
  view_ = view;
  ui_ = ui;
  physics_ = physics;
  eventSystem_ = eventSystem;
  playerState_ = playerState;
  
  auto scripts = level->components(SCRIPT_TYPE);

  for (Component* script : scripts) {
    setupComponent(script);
  }
}

void ScriptManager::update(float dt) {  
  for (auto state : states_) {
    state->update(dt);
  }
  
  Array<LuaState*> removeables = states_;
  
  for(LuaState* state : removeables) {
    if (state->isMarkedForDeletion()) {
      states_.removeObject(state);
      SAFE_DELETE(state);
    }
  }
  
}

void ScriptManager::setupComponent(Component* script) {
  String scriptName = script->attr(SCRIPT_KEY_SCRIPT).string();
  String scriptFile = CCFileUtils::fullPathFromRelativePath(scriptName.replace("lua", "luac").c_str());
  
  /* 
   design issue with an assumption that scripts *are* their type
   this allows us to get scripts by their subtype ie. component:get_all('launchable')
   
   {
   "type": "script",
   "script": "bla"
   }
   
   becomes 
   
   {
   "type": "bla",
   "script: "bla"
   }
   */
  
  level_->removeComponent(script);
  String newType = scriptName.replace(".lua", "");
  script->setType(newType);
  level_->addComponent(script);
  
  LuaState* state = LuaState::state(script, eventSystem_, level_, ui_, view_, physics_, playerState_);
  state->setTag(script->label());
  state->setup();
  state->loadScript(scriptFile);
  setGlobals(state, script->attrs()); 
  state->run();
  
  states_.addObject(state); 
}

void ScriptManager::tearDownComponent(Component *component) {
  for (LuaState* state : states_) {
    if (state->getTag() == component->label()) {
      state->markForDeletion();
    }
  }
}
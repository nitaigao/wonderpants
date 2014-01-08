#include "ParticleEntityManager.h"

#include "Component.h"
#include "Value.h"
#include "Level.h"

#include "Common.h"

#include "GameView.h"

static String PARTICLE_TYPE = "particle";
static String PARTICLE_KEY_Z = "z";
static String PARTICLE_KEY_DATA = "data";
static String PARTICLE_KEY_OFFSET_X = "x";
static String PARTICLE_KEY_OFFSET_Y = "y";


static String SPATIAL_TYPE = "spatial";
static String SPATIAL_KEY_X = "x";
static String SPATIAL_KEY_Y = "y";
static String SPATIAL_KEY_ROTATION = "rotation";

EntityManager* ParticleEntityManager::clone() {
  return new ParticleEntityManager();
}

void ParticleEntityManager::setup(Level* level, IGameView* view, IGameUI* ui, Physics* physics, EventSystem* eventSystem, PlayerState* playerState) {
  level_ = level;
  view_ = view;
  
  Array<Component*> particles = level->components("particle");
  
  for (Component* particle : particles) {
    setupComponent(particle);
  }
}

void ParticleEntityManager::update(float dt) {

}

void ParticleEntityManager::setupComponent(Component* particle) {
  String data = particle->attr(PARTICLE_KEY_DATA).string();
  
  int offsetX = particle->attr(PARTICLE_KEY_OFFSET_X).intValue();
  int offsetY = particle->attr(PARTICLE_KEY_OFFSET_Y).intValue();
  
  int z = particle->attr(PARTICLE_KEY_Z).intValue();
  Component* spatial = level_->component(SPATIAL_TYPE, particle->label());
  int x = spatial->attr(SPATIAL_KEY_X).intValue();
  int y = spatial->attr(SPATIAL_KEY_Y).intValue();
  
  view_->addParticle(data, x, y, z, offsetX, offsetY, particle->label(), spatial);
}

void ParticleEntityManager::tearDownComponent(Component *component) {
  
}
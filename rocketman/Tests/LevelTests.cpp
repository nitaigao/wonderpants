#include "LevelTests.h"

#include <gtest/gtest.h>

#include "Level.h"
#include "Entity.h"
#include "Component.h"

TEST(LevelTests, FindsComponentByType) {
  Entity* e = new Entity();
  Component* c = new Component();
  c->setAttr("a", 1);
  c->setAttr("type", "type");
  e->addComponent(c);
  
  Level* level = new Level();
  level->addEntity(e);
  
  delete e;
  
  ASSERT_EQ(level->components("type").first()->attr("a").intValue(), 1);
}

TEST(LevelTests, DeletesComponent) {
  Level* level = new Level();

  for (int i = 0; i < 2; i++) {
    Entity* e = new Entity();
    Component* c = new Component();
    c->setAttr("a", 1);
    c->setAttr("type", "type");
    e->addComponent(c);
    
    level->addEntity(e);
    
    delete e;
  }
  
  level->destroyComponents(1);
  
  ASSERT_FALSE(level->component("type", 0)->isMarkedForDeletion());
  ASSERT_TRUE(level->component("type", 1)->isMarkedForDeletion());

  ASSERT_TRUE(level->components("type").second()->isMarkedForDeletion());
}

TEST(LevelTests, DestroysComponent) {
  Entity* e = new Entity();
  Component* c = new Component();
  c->setAttr("a", 1);
  c->setAttr("type", "type");
  e->addComponent(c);
  
  Level* level = new Level();
  level->addEntity(e);
  
  delete e;
  
  level->removeComponent(c);
  
  ASSERT_EQ(level->components("type").count(), 0);
}

TEST(LevelTests, EmptyComponentsByType) {
  Level* level = new Level();
  level->components("hello");
}

TEST(LevelTests, RemovesComponent) {
  Entity e;
  
  Component* c1 = new Component();
  c1->setAttr("script", "bla.lua");
  c1->setAttr("type", "script");
  e.addComponent(c1);
  
  Component* c2 = new Component();
  c2->setAttr("script", "zoom.lua");
  c2->setAttr("type", "script");
  e.addComponent(c2);
  
  Level* level = new Level();
  int label = level->addEntity(&e);
 
  level->removeComponent(c2);
  
  Component* cc1 = level->component("script", label);
  
  ASSERT_EQ(cc1->attr("script").string().str(), "bla.lua");
  
}
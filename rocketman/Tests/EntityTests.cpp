#include "EntityTests.h"

#include <gtest/gtest.h>

#include "Entity.h"
#include "Component.h"

TEST(EntityTests, OverridesDuplicateSpatials) {
  Entity entity;
  
  Component* componentA = new Component();
  componentA->setAttr("type", "spatial");
  componentA->setAttr("x", 1);
  entity.addComponent(componentA);
  
  Component* componentB = new Component();
  componentB->setAttr("type", "spatial");
  componentB->setAttr("x", 2);
  entity.addComponent(componentB);
  
  entity.prefabOverride();
  
  ASSERT_EQ(entity.components().count(), 1);
  ASSERT_EQ(entity.components().first()->attr("x").intValue(), 1);
}

/*TEST(EntityTests, OverridesDuplicateScripts) {
  Entity entity;
  
  Component* componentA = new Component();
  componentA->setAttr("type", "script");
  componentA->setAttr("script", "left.lua");
  componentA->setAttr("a", 1);
  entity.addComponent(componentA);
  
  Component* componentB = new Component();
  componentB->setAttr("type", "script");
  componentB->setAttr("script", "left.lua");
  componentB->setAttr("a", 2);
  entity.addComponent(componentB);
  
  entity.prefabOverride();
  
  ASSERT_EQ(entity.components().count(), 1);
  ASSERT_EQ(entity.components().first()->attr("a").intValue(), 1);
}

TEST(EntityTests, DoesntOverridesDifferentScripts) {
  Entity entity;
  
  Component* componentA = new Component();
  componentA->setAttr("type", "script");
  componentA->setAttr("script", "right.lua");
  entity.addComponent(componentA);
  
  Component* componentB = new Component();
  componentB->setAttr("type", "script");
  componentB->setAttr("script", "left.lua");
  entity.addComponent(componentB);
  
  entity.prefabOverride();
  
  ASSERT_EQ(entity.components().count(), 2);
  ASSERT_TRUE(entity.components().first()->attr("script").string() == "right.lua");
  ASSERT_TRUE(entity.components().second()->attr("script").string() == "left.lua");
}


TEST(EntityTests, LeavesTheDefaultComponent) {
  Entity entity;
  
  Component* componentA = new Component();
  componentA->setAttr("type", "script");
  componentA->setAttr("script", "left.lua");
  componentA->setAttr("a", 1);
  entity.addComponent(componentA);
  
  entity.prefabOverride();
  
  ASSERT_EQ(entity.components().count(), 1);
}*/
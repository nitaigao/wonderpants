#include "ComponentTests.h"

#include <gtest/gtest.h>

#include "Component.h"

TEST(ComponentTests, SetAttr) {
  Component component;
  component.setAttr("a", 1);
  ASSERT_TRUE(component.attr("a").intValue() == 1);
}

TEST(ComponentTests, SetAttrNotEqual) {
  Component component;
  component.setAttr("a", 2);
  ASSERT_FALSE(component.attr("a").intValue() == 1);
}

TEST(ComponentTests, TypeHash) {
  Component component;
  component.setAttr("type", "abc");
  ASSERT_TRUE(String("abc").hash() == component.typeHash());
}

TEST(ComponentTests, NotTypeHash) {
  Component component;
  component.setAttr("type", "abcd");
  ASSERT_FALSE(String("abc").hash() == component.typeHash());
}


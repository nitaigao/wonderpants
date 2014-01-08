#include "StringTests.h"

#include <gtest/gtest.h>

#include "Common.h"

TEST(StringTests, Equal) {
  ASSERT_TRUE(String("a") == String("a"));
}

TEST(StringTests, NotEqual) {
  ASSERT_FALSE(String("a") != String("a"));
}

TEST(StringTests, NotEqualEqual) {
  ASSERT_FALSE(String("b") == String("a"));
}

TEST(StringTests, NotEqualNotEqual) {
  ASSERT_TRUE(String("b") != String("a"));
}

TEST(StringTests, ReplaceExistingText) {  
  String a("hello");
  String result = a.replace("h", "");  
  ASSERT_TRUE(result == "ello");  
}

TEST(StringTests, ReplaceNonExistingText) {  
  String a("hello");
  String result = a.replace("b", "");  
  ASSERT_TRUE(result == "hello");  
}

TEST(StringTests, Contains) {  
  String a("hello");
  ASSERT_TRUE(a.contains("e"));
  ASSERT_FALSE(a.contains("d"));
}

TEST(StringTests, MapKey) {
  std::map<String, std::vector<int>> list;
  list["a"].push_back(1);
  list["b"].push_back(2);
  
  ASSERT_EQ(list["a"].front(), 1);
}

TEST(StringTests, AssignsCorrectly) {
  String a("a");
  String b = a;
  ASSERT_TRUE(b.length());
}

TEST(StringTests, CopiesCorrectly) {
  String a("a");
  String b(a);
  ASSERT_TRUE(b.length());
}

TEST(StringTests, PointersCopyCorrectly) {
  String* a = new String("a");
  String* b = new String(*a);
  delete a;
  ASSERT_TRUE(b->length());
  delete b;
}


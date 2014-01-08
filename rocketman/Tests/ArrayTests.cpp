#include "ArrayTests.h"

#include <gtest/gtest.h>

#include "Array.h"

TEST(ArrayTests, SizeIncreases) {
  Array<int> array;
  array.addObject(1);
  array.addObject(2);
  ASSERT_EQ(2, array.count());
}

TEST(ArrayTests, ReversesArray) {
  Array<int> array;
  array.addObject(1);
  array.addObject(2);
  Array<int> reversed = array.reverse();
  ASSERT_EQ(reversed.first(), 2);
}

TEST(ArrayTests, FirstGivesFirstElement) {
  Array<int> array;
  array.addObject(1);
  ASSERT_EQ(array.first(), 1);
}

TEST(ArrayTests, SecondGivesSecondElement) {
  Array<int> array;
  array.addObject(1);
  array.addObject(2);
  ASSERT_EQ(array.second(), 2);
}

TEST(ArrayTests, ThirdGivesThirdElement) {
  Array<int> array;
  array.addObject(1);
  array.addObject(2);
  array.addObject(3);
  ASSERT_EQ(array.third(), 3);
}

TEST(ArrayTests, RemovesAnElement) {
  int a = 1;
  Array<int> array;
  array.addObject(a);
  array.removeObject(a);
  ASSERT_EQ(array.count(), 0);
}

TEST(ArrayTests, SubArrayReturnsEmptyArray) {
  Array<int> array;
  ASSERT_EQ(array.subArray(0, 0).count(), 0);
}

TEST(ArrayTests, SubArrayReturnsArrayWithOneObject) {
  Array<int> array;
  array.addObject(1);
  ASSERT_EQ(array.subArray(0, 1).count(), 1);
}

TEST(ArrayTests, CopiesArrayFromArray) {
  Array<int> a;
  a.addObject(1);
  
  Array<int> b = Array<int>::fromArray(a);
  ASSERT_EQ(b.count(), a.count());
  ASSERT_EQ(a.first(), b.first());
}

TEST(ArrayTests, ConstructsArrayFromObjects) {
  Array<int> a = Array<int>::fromObjects(1, 2, 3);
  ASSERT_EQ(a.count(), 3);
  ASSERT_EQ(a.first(), 1);
  ASSERT_EQ(a.second(), 2);
  ASSERT_EQ(a.third(), 3);
}
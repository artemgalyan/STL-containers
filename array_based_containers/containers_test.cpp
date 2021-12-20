#include "gtest/gtest.h"
#include "array_containers.h"
#include "array_containers.cpp"
#include <numeric>

#define NUMBER_WANTED_TO_BE_TESTED_WITH Deque<size_t>::npos
#define TEST_TYPE size_t

int NUMBER_TO_TEST = NUMBER_WANTED_TO_BE_TESTED_WITH > std::numeric_limits<TEST_TYPE>::max()
    ? NUMBER_WANTED_TO_BE_TESTED_WITH
    : std::numeric_limits<TEST_TYPE>::max();

using namespace Containers;

TEST(Deque, exceptions) {
  Deque<int> d;
  EXPECT_ANY_THROW(d.At(-1));
  EXPECT_ANY_THROW(d.At(10));
  EXPECT_ANY_THROW(d.Pop_back());
  EXPECT_ANY_THROW(d.Pop_front());
  EXPECT_ANY_THROW(d.Top());
  EXPECT_ANY_THROW(d.Front());
}

TEST(stack, general_test) {
  Stack<int> s;
  for (int i = 0; i < NUMBER_TO_TEST; ++i)
    s.Push(i);
  for (int i = NUMBER_TO_TEST - 1; i >= 0; --i) {
    ASSERT_EQ(i, s.Top());
    s.Pop();
  }
}

TEST(Deque, push_and_pop_front_test) {
  Deque<int> d;
  for (int i = 0; i < NUMBER_TO_TEST; ++i)
    d.Push_back(i);
  for (int i = 0; i < NUMBER_TO_TEST; ++i) {
    ASSERT_EQ(i, d.Front());
    d.Pop_front();
  }
  ASSERT_TRUE(d.IsEmpty());
  for (int i = 0; i < NUMBER_TO_TEST; ++i)
    d.Push_back(i);
  for (int i = NUMBER_TO_TEST - 1; i >= 0; --i) {
    ASSERT_EQ(d.Top(), i);
    d.Pop_back();
  }
  for (int i = 0; i < NUMBER_TO_TEST; ++i)
    d.Push_front(i);
  for (int i = NUMBER_TO_TEST - 1; i >= 0; --i) {
    ASSERT_EQ(i, d.Front());
    d.Pop_front();
  }
  ASSERT_TRUE(d.IsEmpty());
}
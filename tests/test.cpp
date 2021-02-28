// Copyright 2020 Your Name <your_email>

#include <gtest/gtest.h>
#include "Stack.hpp"
#include "StackNoCopy.hpp"

TEST(Example, EmptyTest) {
  EXPECT_TRUE(true);
}

TEST(Stack, Push_rvalue) {
  Stack<double> a;

  a.push(5.7);
  EXPECT_EQ(a.head(), 5.7);

  double val = 9;
  a.push(std::move(val));
  EXPECT_EQ(a.head(), 9.0);
}

TEST(Stack, Push_lvalue) {
  Stack<double> a;
  EXPECT_THROW(a.head(), std::runtime_error);

  double val1 = 5.7;

  a.push(val1);
  EXPECT_EQ(a.head(), val1);
}

TEST(Stack, Pop) {
  Stack<double> a;
  EXPECT_THROW(a.pop(), std::runtime_error);

  double val1 = 5.7;
  double val2 = 10.3;
  double val3 = 9;

  a.push(val1);
  a.push(val2);
  a.push(val3);
  a.pop();
  EXPECT_EQ(a.head(), val2);
  a.pop();
  EXPECT_EQ(a.head(), val1);
  a.pop();
  EXPECT_THROW(a.head(), std::runtime_error);
}

TEST(Stack, Head) {
  Stack<int> a;
  EXPECT_THROW(a.head(), std::runtime_error);
  a.push(5);
  EXPECT_EQ(a.head(), 5);
  a.push(10);
  EXPECT_EQ(a.head(), 10);
  a.pop();
  EXPECT_EQ(a.head(), 5);
}

TEST(Stack, Is_Move) {
  EXPECT_TRUE(std::is_move_constructible<Stack<int>>::value);
  EXPECT_TRUE(std::is_move_assignable<Stack<int>>::value);
}

TEST(Stack, Is_Copy) {
  EXPECT_FALSE(std::is_copy_constructible<Stack<int>>::value);
  EXPECT_FALSE(std::is_copy_assignable<Stack<int>>::value);
}

TEST(StackNoCopy, head) {
  StackNoCopy<double> a;
  EXPECT_THROW(a.head(), std::runtime_error);
}

template <typename T>
struct Test1
{
  T first;
  T second;
};

TEST(StackNoCopy, Push_rvalue_Pop_rvalue) {
  StackNoCopy<double> a;
  a.push(5.7);
  EXPECT_EQ(a.head(), 5.7);
  double val = 9;
  a.push(std::move(val));
  EXPECT_EQ(a.pop(), 9.0);
}

TEST(StackNoCopy, Push_emplace) {
  StackNoCopy<Test1<int>> a;
  a.push_emplace(1, 2);
  EXPECT_EQ(a.head().first, 1);
}

TEST(StackNoCopy, Is_Move) {
  EXPECT_TRUE(std::is_move_constructible<StackNoCopy<int>>::value);
  EXPECT_TRUE(std::is_move_assignable<StackNoCopy<int>>::value);
}

TEST(StackNoCopy, Is_Copy) {
  EXPECT_FALSE(std::is_copy_constructible<StackNoCopy<int>>::value);
  EXPECT_FALSE(std::is_copy_assignable<StackNoCopy<int>>::value);
}
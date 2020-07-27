// Project Euler #254: Sums of Digit Factorials
#ifndef TEST
#define TEST
#endif

#include "gtest/gtest.h"
#include "sum_of_digits_254.cpp"
#include <iterator>
using namespace std;

void move_f_to(F &f, int i){
  for (; i > 0; i--){
    f++;
  }
}

namespace {
  TEST(SumOfDigit, F){
    auto f = F(0);
    EXPECT_EQ(f.get_value(), 0);
    move_f_to(f, 3);
    EXPECT_EQ(f.get_value(), 3);
    EXPECT_EQ(f.get_fact_sum(), 6);
    move_f_to(f, 10);
    EXPECT_EQ(f.get_value(), 3 + 10);
    EXPECT_EQ(f.get_fact_sum(), 1 + 6);
  }

  TEST(SumOfDigit, FIter){
    auto fi = FIter();
    auto fi_it = fi.begin();
    EXPECT_EQ((*fi_it).get_value(), 0);
    advance(fi_it, 11);
    EXPECT_EQ((*fi_it).get_value(), 11);
    EXPECT_EQ((*fi_it).get_fact_sum(), 1 + 1 );

  }
}

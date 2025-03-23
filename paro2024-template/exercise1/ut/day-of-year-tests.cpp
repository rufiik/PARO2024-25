#include "gtest/gtest.h"
#include "day-of-year.hpp"

struct DayOfYearTestSuite {};


TEST(DayOfYearTestSuite, dummyTest)
{
  ASSERT_TRUE(true);
}


TEST(DayOfYearTestSuite, January1stIsFitstDayOfYear)
{
  ASSERT_EQ(dayOfYear(1, 1, 2020), 1);
}

TEST(DayOfYearTestSuite, February1stIsFitstDayOfYear)
{
  ASSERT_EQ(dayOfYear(2, 1, 2020), 32);
}

TEST(DayOfYearTestSuite, March1stIsFitstDayOfLeapYear)
{
  ASSERT_EQ(dayOfYear(3, 1, 2020), 61);
}

TEST(DayOfYearTestSuite, March1stIsFitstDayOfNotLeapYear)
{
  ASSERT_EQ(dayOfYear(3, 1, 2019), 60);
}


TEST(DayOfYearTestSuite, IsLeapYearTest2020)
{
  ASSERT_EQ(isLeap(2020), true);
}

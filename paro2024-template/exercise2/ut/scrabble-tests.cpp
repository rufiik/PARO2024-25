#include "gtest/gtest.h"
#include "scrabble.hpp"

struct ScrabbleTestSuite {};

TEST(ScrabbleTestSuite, dummyTest)
{
  ASSERT_TRUE(true);
}


TEST(ScrabbleTestSuite, emptyWord)
{
  ASSERT_EQ(countScrabbleScore(""), 0);
}


TEST(ScrabbleTestSuite, singleLetter)
{
  ASSERT_EQ(countScrabbleScore('Z'), 10);
}

TEST(ScrabbleTestSuite, smallLetter)
{
  ASSERT_EQ(countScrabbleScore('z'), 10);
}
TEST(ScrabbleTestSuite, testWords)
{
  ASSERT_EQ(countScrabbleScore('zupa'), 15);
  ASSERT_EQ(countScrabbleScore('zUPa'), 15);
  ASSERT_EQ(computeScrabbleScore("HeLLo"), 8);

}
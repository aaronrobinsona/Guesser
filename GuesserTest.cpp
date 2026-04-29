/**
 * Unit Tests for the class
**/

#include <gtest/gtest.h>
#include "Guesser.h"

class GuesserTest : public ::testing::Test
{
	protected:
		GuesserTest(){} //constructor runs before each test
		virtual ~GuesserTest(){} //destructor cleans up after tests
		virtual void SetUp(){} //sets up before each test (after constructor)
		virtual void TearDown(){} //clean up after each test, (before destructor)
};

// Example "smoke test" (can be deleted)
TEST(GuesserTest, smoke_test)
{
  Guesser object("Secret");
  ASSERT_EQ( 1+1, 2 );
}
//Ending WhiteSpace Test
TEST(GuesserTest, whitespace_test)
{
	Guesser object("Secret2");
	bool match_test = object.match("Secret2 ");
	ASSERT_EQ(true, match_test);
}
//Distance Exact Match
TEST(GuesserTest, distance_exact_match)
{
    Guesser g("secret3");
    ASSERT_EQ(0, g.distance("secret3"));
}
//Distance Same Length, Different Characters
TEST(GuesserTest, distance_same_length_different_chars)
{
    Guesser g("secret3");
    ASSERT_EQ(1, g.distance("secret4"));
}
//Distance secret match but with longer guess
TEST(GuesserTest, distance_guess_longer_than_secret)
{
    Guesser g("sec");
    ASSERT_EQ(2, g.distance("secccc"));
}

//distance  shorter guess longer secret
TEST(GuesserTest, distance_guess_shorter_than_secret)
{
    Guesser g("secret");
    ASSERT_EQ(3, g.distance("se"));
}

TEST(GuesserTest, distance_capped_at_secret_length)
{
    Guesser g("abc");
    ASSERT_EQ(3, g.distance("zzzzzzzz"));
}
//Constructor Test
TEST(GuesserTest, constructor_truncates_long_secret)
{
    std::string long_secret(40, 'a'); // 40 'a's
    Guesser g(long_secret);

    ASSERT_EQ(32, g.distance(std::string(32, 'b'))); // max distance = 32
}
//exact match
TEST(GuesserTest, match_correct_guess)
{
    Guesser g("secret");
    ASSERT_TRUE(g.match("secret"));
}
//3 Wrong Guesses Locked
TEST(GuesserTest, match_decrements_remaining)
{
    Guesser g("secret");

    ASSERT_FALSE(g.match("secrex"));
    ASSERT_FALSE(g.match("secrex"));
    ASSERT_FALSE(g.match("secrex"));
}
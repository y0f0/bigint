#pragma once

#include "../../solve.h"
#include "../tests_from_problem_text/tests_from_problem_text.h"

#include "gtest/gtest.h"

void testTwoFilesWithCommon(std::string path, std::string common)
{
	testTwoFile(common + "in/" + path + ".in", common + "out/" + path + ".out");
}

namespace addition
{
	std::string common = "Google_tests/tests_addition/";
}

TEST(AdditionBigNumbers, PositiveAndPositive)
{
	testTwoFilesWithCommon("++", addition::common);
}

TEST(AdditionBigNumbers, PositiveAndNegaitve)
{
	testTwoFilesWithCommon("+-", addition::common);
}

TEST(AdditionBigNumbers, NegaitveAndPositive)
{
	testTwoFilesWithCommon("-+", addition::common);
}

TEST(AdditionBigNumbers, NegaitveAndNegaitve)
{
	testTwoFilesWithCommon( "--", addition::common);
}

TEST(AdditionBigNumbers, PositiveAndZero)
{
	testTwoFilesWithCommon( "+0", addition::common);
}

TEST(AdditionBigNumbers, ZeroAndPositive)
{
	testTwoFilesWithCommon("0+", addition::common);
}

TEST(AdditionBigNumbers, NegaitveAndZero)
{
	testTwoFilesWithCommon( "-0", addition::common);
}

TEST(AdditionBigNumbers, ZeroAndNegaitve)
{
	testTwoFilesWithCommon("0-", addition::common);
}

TEST(AdditionBigNumbers, ZeroAndZero)
{
	testTwoFilesWithCommon( "00", addition::common);
}



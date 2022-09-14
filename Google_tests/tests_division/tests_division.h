#pragma once

#include "../../solve.h"
#include "../tests_addition/tests_addition.h"
#include "../tests_from_problem_text/tests_from_problem_text.h"

#include "gtest/gtest.h"

namespace division
{
	std::string common = "Google_tests/tests_division/";
}

TEST(DivisionBigNumbers, PositiveAndPositive)
{
	testTwoFilesWithCommon("++", division::common);
}

TEST(DivisionBigNumbers, PositiveAndNegaitve)
{
	testTwoFilesWithCommon("+-", division::common);
}

TEST(DivisionBigNumbers, NegaitveAndPositive)
{
	testTwoFilesWithCommon("-+", division::common);
}

TEST(DivisionBigNumbers, NegaitveAndNegaitve)
{
	testTwoFilesWithCommon("--", division::common);
}

TEST(DivisionBigNumbers, PositiveAndZero)
{
	testTwoFilesWithCommon("+0", division::common);
}

TEST(DivisionBigNumbers, ZeroAndPositive)
{
	testTwoFilesWithCommon("0+", division::common);
}

TEST(DivisionBigNumbers, NegaitveAndZero)
{
	testTwoFilesWithCommon("-0", division::common);
}

TEST(DivisionBigNumbers, ZeroAndNegaitve)
{
	testTwoFilesWithCommon("0-", division::common);
}

TEST(DivisionBigNumbers, ZeroAndZero)
{
	testTwoFilesWithCommon("00", division::common);
}

#pragma once

#include "../../solve.h"
#include "../tests_addition/tests_addition.h"
#include "../tests_from_problem_text/tests_from_problem_text.h"

#include "gtest/gtest.h"

namespace subtraction
{
	std::string common = "Google_tests/tests_subtraction/";
}

TEST(SubtractinoBigNumbers, PositiveAndPositive)
{
	testTwoFilesWithCommon("++", subtraction::common);
}

TEST(SubtractinoBigNumbers, PositiveAndNegaitve)
{
	testTwoFilesWithCommon("+-", subtraction::common);
}

TEST(SubtractinoBigNumbers, NegaitveAndPositive)
{
	testTwoFilesWithCommon("-+", subtraction::common);
}

TEST(SubtractinoBigNumbers, NegaitveAndNegaitve)
{
	testTwoFilesWithCommon("--", subtraction::common);
}

TEST(SubtractinoBigNumbers, PositiveAndZero)
{
	testTwoFilesWithCommon("+0", subtraction::common);
}

TEST(SubtractinoBigNumbers, ZeroAndPositive)
{
	testTwoFilesWithCommon("0+", subtraction::common);
}

TEST(SubtractinoBigNumbers, NegaitveAndZero)
{
	testTwoFilesWithCommon("-0", subtraction::common);
}

TEST(SubtractinoBigNumbers, ZeroAndNegaitve)
{
	testTwoFilesWithCommon("0-", subtraction::common);
}

TEST(SubtractinoBigNumbers, ZeroAndZero)
{
	testTwoFilesWithCommon("00", subtraction::common);
}

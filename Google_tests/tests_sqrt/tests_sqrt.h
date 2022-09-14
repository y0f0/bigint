#pragma once

#include "../../solve.h"
#include "../tests_addition/tests_addition.h"
#include "../tests_from_problem_text/tests_from_problem_text.h"

#include "gtest/gtest.h"

namespace sqrt
{
	std::string common = "Google_tests/tests_sqrt/";
}

TEST(SqrtBigNumbers, 0)
{
	testTwoFilesWithCommon("0", sqrt::common);
}

TEST(SqrtBigNumbers, 1)
{
	testTwoFilesWithCommon("1", sqrt::common);
}

TEST(SqrtBigNumbers, 2)
{
	testTwoFilesWithCommon("2", sqrt::common);
}

TEST(SqrtBigNumbers, 3)
{
	testTwoFilesWithCommon("3", sqrt::common);
}

TEST(SqrtBigNumbers, 4)
{
	testTwoFilesWithCommon("4", sqrt::common);
}

TEST(SqrtBigNumbers, NaN)
{
	testTwoFilesWithCommon("NaN", sqrt::common);
}

TEST(Unary, 0)
{
	testTwoFilesWithCommon("Unary", sqrt::common);
}
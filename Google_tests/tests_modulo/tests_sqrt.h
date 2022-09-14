#pragma once

#include "../../solve.h"
#include "../tests_addition/tests_addition.h"
#include "../tests_from_problem_text/tests_from_problem_text.h"

#include "gtest/gtest.h"

namespace modulo
{
	std::string common = "Google_tests/tests_modulo/";
}

TEST(ModuloBigNumbers, PositiveAndPositive)
{
	testTwoFilesWithCommon("++", modulo::common);
}

TEST(ModuloBigNumbers, PositiveAndNegaitve)
{
	testTwoFilesWithCommon("+-", modulo::common);
}

TEST(ModuloBigNumbers, NegaitveAndPositive)
{
	testTwoFilesWithCommon("-+", modulo::common);
}

TEST(ModuloBigNumbers, NegaitveAndNegaitve)
{
	testTwoFilesWithCommon("--", modulo::common);
}

TEST(ModuloBigNumbers, PositiveAndZero)
{
	testTwoFilesWithCommon("+0", modulo::common);
}

TEST(ModuloBigNumbers, ZeroAndPositive)
{
	testTwoFilesWithCommon("0+", modulo::common);
}

TEST(ModuloBigNumbers, NegaitveAndZero)
{
	testTwoFilesWithCommon("-0", modulo::common);
}

TEST(ModuloBigNumbers, ZeroAndNegaitve)
{
	testTwoFilesWithCommon("0-", modulo::common);
}

TEST(ModuloBigNumbers, ZeroAndZero)
{
	testTwoFilesWithCommon("00", modulo::common);
}

#pragma once

#include "../../solve.h"
#include "../tests_addition/tests_addition.h"
#include "../tests_from_problem_text/tests_from_problem_text.h"

#include "gtest/gtest.h"

namespace paths
{
	std::string is_true = "true.out";
	std::string is_false = "false.out";
}	 // namespace paths

void testTwoFileComparisonOperators(std::string input, std::string output)
{
	std::string common = "Google_tests/tests_comparison_operators/";
	testTwoFile(common + "in/" + input, common + "out/" + output);
}

/* < */
TEST(Comparison_operators, LessSmall)
{
	testTwoFileComparisonOperators("<s.in", paths::is_false);
}

TEST(Comparison_operators, LessBig)
{
	testTwoFileComparisonOperators("<b.in", paths::is_true);
}

TEST(Comparison_operators, LessEqual)
{
	testTwoFileComparisonOperators("<e.in", paths::is_false);
}

/* <= */
TEST(Comparison_operators, LessOrEqualSmall)
{
	testTwoFileComparisonOperators("<=s.in", paths::is_false);
}

TEST(Comparison_operators, LessOrEqualBig)
{
	testTwoFileComparisonOperators("<=b.in", paths::is_true);
}

TEST(Comparison_operators, LessOrEqualEqual)
{
	testTwoFileComparisonOperators("<=e.in", paths::is_true);
}

/* > */
TEST(Comparison_operators, GreaterSmall)
{
	testTwoFileComparisonOperators(">s.in", paths::is_true);
}

TEST(Comparison_operators, GreaterBig)
{
	testTwoFileComparisonOperators(">b.in", paths::is_false);
}

TEST(Comparison_operators, GreaterEqual)
{
	testTwoFileComparisonOperators(">e.in", paths::is_false);
}

/* >= */
TEST(Comparison_operators, GreaterOrEqualSmall)
{
	testTwoFileComparisonOperators(">=s.in", paths::is_true);
}

TEST(Comparison_operators, GreaterOrEqualBig)
{
	testTwoFileComparisonOperators(">=b.in", paths::is_false);
}

TEST(Comparison_operators, GreaterOrEqualEqual)
{
	testTwoFileComparisonOperators(">=e.in", paths::is_true);
}

/* == */
TEST(Comparison_operators, EqualSmall)
{
	testTwoFileComparisonOperators("==s.in", paths::is_false);
}

TEST(Comparison_operators, EqualBig)
{
	testTwoFileComparisonOperators("==b.in", paths::is_false);
}

TEST(Comparison_operators, EqualEqual)
{
	testTwoFileComparisonOperators("==e.in", paths::is_true);
}

/* != */
TEST(Comparison_operators, NotEqualSmall)
{
	testTwoFileComparisonOperators("!=s.in", paths::is_true);
}

TEST(Comparison_operators, NotEqualBig)
{
	testTwoFileComparisonOperators("!=b.in", paths::is_true);
}

TEST(Comparison_operators, NotEqualEqual)
{
	testTwoFileComparisonOperators("!=e.in", paths::is_false);
}

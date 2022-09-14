#pragma once

#include "../../solve.h"
#include "../tests_addition/tests_addition.h"
#include "../tests_from_problem_text/tests_from_problem_text.h"

#include "gtest/gtest.h"

namespace NaN
{
	std::string common = "Google_tests/tests_nan/";
}

void testIsNan(const std::string& path)
{
	testTwoFile(NaN::common + "in/" + path + ".in", NaN::common + "out/NaN.out");
}

void testIsFalse(const std::string& path)
{
	testTwoFile(NaN::common + "in/" + path + ".in", NaN::common + "out/false.out");
}

void testIsTrue(const std::string& path)
{
	testTwoFile(NaN::common + "in/" + path + ".in", NaN::common + "out/true.out");
}



/* + */
TEST(NaN_addition, Right)
{
	testIsNan("sum_NaN+");
}

TEST(NaN_addition, Left)
{
	testIsNan("sum_+Nan");
}

TEST(NaN_addition, NaN)
{
	testIsNan("sum_NaNNaN");
}

/* - */

TEST(NaN_subtraction, Right)
{
	testIsNan("sub_NaN+");
}

TEST(NaN_subtraction, Left)
{
	testIsNan("sub_+Nan");
}

TEST(NaN_subtraction, NaN)
{
	testIsNan("sub_NaNNaN");
}

/* * */
TEST(NaN_multiplicatioin, Right)
{
	testIsNan("mul_NaN+");
}

TEST(NaN_multiplicatioin, Left)
{
	testIsNan("mul_+Nan");
}

TEST(NaN_multiplicatioin, NaN)
{
	testIsNan("mul_NaNNaN");
}

/* / */
TEST(NaN_division, Right)
{
	testIsNan("div_NaN+");
}

TEST(NaN_division, Left)
{
	testIsNan("div_+Nan");
}

TEST(NaN_division, NaN)
{
	testIsNan("div_NaNNaN");
}

/* % */
TEST(NaN_modulo, Right)
{
	testIsNan("mod_NaN+");
}

TEST(NaN_modulo, Left)
{
	testIsNan("mod_+NaN");
}

TEST(NaN_modulo, NaN)
{
	testIsNan("mod_NaNNaN");
}

/* ~ */
TEST(NaN_sqrt, Negative)
{
	testIsNan("sqrt_-");
}

TEST(NaN_sqrt, NaN)
{
	testIsNan("sqrt_NaN");
}

/* _ (unary minus)*/
TEST(NaN_unary_minus, NaN)
{
	testIsNan("__NaN");
}

/* < */
TEST(NaN_less, NumberNaN)
{
	testIsFalse("<_+NaN");
}

TEST(NaN_less, NaNNumber)
{
	testIsFalse("<_NaN+");
}

TEST(NaN_less, NaN)
{
	testIsFalse("<_NaN");
}

/* <= */
TEST(NaN_less_or_equal, NumberNaN)
{
	testIsFalse("<=_+NaN");
}

TEST(NaN_less_or_equal, NaNNumber)
{
	testIsFalse("<=_NaN+");
}

TEST(NaN_less_or_equal, NaN)
{
	testIsFalse("<=_NaN");
}

/* > */
TEST(NaN_less_greater, NumberNaN)
{
	testIsFalse(">_+NaN");
}

TEST(NaN_less_greater, NaNNumber)
{
	testIsFalse(">_NaN+");
}

TEST(NaN_less_greater, NaN)
{
	testIsFalse(">_NaN");
}

/* >= */
TEST(NaN_greater_or_equal, NumberNaN)
{
	testIsFalse(">=_+NaN");
}

TEST(NaN_greater_or_equal, NaNNumber)
{
	testIsFalse(">=_NaN+");
}

TEST(NaN_greater_or_equal, NaN)
{
	testIsFalse(">=_NaN");
}

/* == */
TEST(NaN_equality, NumberNaN)
{
	testIsFalse("==_+NaN");
}

TEST(NaN_equality, NaNNumber)
{
	testIsFalse("==_NaN+");
}

TEST(NaN_equality, NaN)
{
	testIsFalse("==_NaN");
}

/* != */
TEST(NaN_not_equality, NumberNaN)
{
	testIsTrue("!=_+NaN");
}

TEST(NaN_not_equality, NaNNumber)
{
	testIsTrue("!=_NaN+");
}

TEST(NaN_not_equality, NaN)
{
	testIsTrue("!=_NaN");
}

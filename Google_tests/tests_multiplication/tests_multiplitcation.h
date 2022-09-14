#pragma once

#include "../../solve.h"
#include "../tests_from_problem_text/tests_from_problem_text.h"

#include "gtest/gtest.h"

void testSmallNumbers(const std::string& input, const std::string& output)
{
	testTwoFile("Google_tests/tests_multiplication/small_numbers/in/" + input + ".in",
				"Google_tests/tests_multiplication/small_numbers/out/" + output + ".out");
}

//TEST(MultiplicationSmallNumbers, PositiveAndPositive)
//{
//	testSmallNumbers("++", "4");
//}
//
//TEST(MultiplicationSmallNumbers, PositiveAndNegaitve)
//{
//	testSmallNumbers("+-", "-4");
//}
//
//TEST(MultiplicationSmallNumbers, NegaitveAndPositive)
//{
//	testSmallNumbers("-+", "-4");
//}
//
//TEST(MultiplicationSmallNumbers, NegaitveAndNegaitve)
//{
//	testSmallNumbers("--", "4");
//}
//
//TEST(MultiplicationSmallNumbers, PositiveAndZero)
//{
//	testSmallNumbers("+0", "0");
//}
//
//TEST(MultiplicationSmallNumbers, ZeroAndPositive)
//{
//	testSmallNumbers("0+", "0");
//}
//
//TEST(MultiplicationSmallNumbers, NegaitveAndZero)
//{
//	testSmallNumbers("-0", "0");
//}
//
//TEST(MultiplicationSmallNumbers, ZeroAndNegaitve)
//{
//	testSmallNumbers("0-", "0");
//}
//
//TEST(MultiplicationSmallNumbers, ZeroAndZero)
//{
//	testSmallNumbers("00", "0");
//}

void testBigNumbers(const std::string& input, const std::string& output)
{
	testTwoFile("Google_tests/tests_multiplication/big_numbers/in/" + input + ".in",
				"Google_tests/tests_multiplication/big_numbers/out/" + output + ".out");
}

TEST(MultiplicationBigNumbers, PositiveAndPositive)
{
	testBigNumbers("++", "+");
}

TEST(MultiplicationBigNumbers, PositiveAndNegaitve)
{
	testBigNumbers("+-", "-");
}

TEST(MultiplicationBigNumbers, NegaitveAndPositive)
{
	testBigNumbers("-+", "-");
}

TEST(MultiplicationBigNumbers, NegaitveAndNegaitve)
{
	testBigNumbers("--", "+");
}

TEST(MultiplicationBigNumbers, PositiveAndZero)
{
	testBigNumbers("+0", "0");
}

TEST(MultiplicationBigNumbers, ZeroAndPositive)
{
	testBigNumbers("0+", "0");
}

TEST(MultiplicationBigNumbers, NegaitveAndZero)
{
	testBigNumbers("-0", "0");
}

TEST(MultiplicationBigNumbers, ZeroAndNegaitve)
{
	testBigNumbers("0-", "0");
}

TEST(MultiplicationBigNumbers, ZeroAndZero)
{
	testBigNumbers("00", "0");
}

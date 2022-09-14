#pragma once

#include "../../solve.h"

#include "gtest/gtest.h"

std::string read_all_lines(std::ifstream& out)
{
	std::string all_lines;
	std::string str;
	while (std::getline(out, str))
	{
		all_lines += str;
		all_lines += "\n";
	}
	return all_lines;
}

void testTwoFile(const std::string& input_path, const std::string& expected_path)
{
	std::ifstream solve_in(input_path);
	if (!solve_in.good())
	{
		ASSERT_TRUE(false) << "solve file is not exists!" << std::endl;
	}
	std::ostringstream solve_out;
	solve(solve_in, solve_out);
	std::string real = solve_out.str();

	std::ifstream expected_out(expected_path);
	if (!expected_out.good())
	{
		ASSERT_TRUE(false) << "expected file is not exists!" << std::endl;
	}
	std::string expected = read_all_lines(expected_out);
	if (expected.empty())
	{
		std::cerr << "expected is empty!";
		ASSERT_EQ("expected is empty!", "");
	}
	if (real.empty())
	{
		std::cerr << "real is empty!";
		ASSERT_EQ("real is empty!", "");
	}
	ASSERT_EQ(real.size(), expected.size());
//	for (int i = 0; i < expected.size(); i++)
//	{
//		ASSERT_EQ(real[i], expected[i]) << "Symbols in " << i << std::endl;
//	}
	ASSERT_EQ(real, expected);
}

TEST(FromGithub, Zero)
{
	testTwoFile(".github/workflows/in0.txt", ".github/workflows/ref0.txt");
}

TEST(FromGithub, First)
{
	testTwoFile(".github/workflows/in1.txt", ".github/workflows/ref1.txt");
}

TEST(FromGithub, Second)
{
	testTwoFile(".github/workflows/in2.txt", ".github/workflows/ref2.txt");
}

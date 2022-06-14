#include "util.h"

#include <algorithm>

bool util::is_10_degree(const MyString& str)
{
	if (str[0] != '1')
		return false;
	for (size_t i = 1; i < str.size(); i++)
		if (str[i] != '0')
			return false;

	return true;
}

MyString util::multiply(MyString first, MyString second)
{
	if (first.length() > second.length())
	{
		std::swap(first, second);
	}

	MyString res("0");
	for (int i = static_cast< int >(first.length()) - 1; i >= 0; --i)
	{
		MyString copy = second;
		int digit = first[i] - '0';
		int transfer = 0;

		for (int j = static_cast< int >(copy.length()) - 1; j >= 0; --j)
		{
			copy[j] = static_cast< char >(((copy[j] - '0') * digit)) + transfer;

			if (copy[j] > 9)
			{
				transfer = (copy[j] / 10);
				copy[j] -= static_cast< char >(transfer * 10);
			}
			else
				transfer = 0;

			copy[j] += '0';
		}

		if (transfer > 0)
		{
			copy.insert(0, new char[]{ static_cast< char >(transfer + '0') }, 1);
		}

		copy.append((first.length() - i - 1), '0');

		res = add(res, copy);
	}

	while (res[0] == '0' && res.length() != 1)
	{
		res.erase(0, 1);
	}

	return res;
}

MyString util::add(MyString first, MyString second)
{
	MyString res = (first.length() > second.length()) ? first : second;
	char transfer = '0';
	int diff = std::abs((int)(first.size() - second.size()));

	if (first.size() > second.size())
	{
		for (int i = 0; i < diff; i++)
		{
			second.insert(0, "0", 1);
		}
	}
	else
	{
		for (int i = 0; i < diff; i++)
		{
			first.insert(0, "0", 1);
		}
	}

	for (int i = static_cast< int >(first.size()) - 1; i >= 0; --i)
	{
		res[i] = static_cast< char >((transfer - '0') + (first[i] - '0') + (second[i] - '0')) + '0';

		if (i != 0)
		{
			if (res[i] > '9')
			{
				res[i] -= 10;
				transfer = '1';
			}
			else
			{
				transfer = '0';
			}
		}
	}
	if (res[0] > '9')
	{
		res[0] -= 10;
		res.insert(0, new char[]{ '1' }, 1);
	}
	return res;
}

MyString util::subtract(MyString first, MyString second)
{
	MyString res = (first.length() > second.length()) ? first : second;
	int diff = std::abs((int)(first.size() - second.size()));

	if (first.size() > second.size())
	{
		for (int i = 0; i < diff; i++)
		{
			second.insert(0, "0", 1);
		}
	}
	else
	{
		for (int i = 0; i < diff; i++)
		{
			first.insert(0, "0", 1);
		}
	}

	for (int i = static_cast< int >(first.length()) - 1; i >= 0; --i)
	{
		if (first[i] < second[i])
		{
			first[i] += 10;
			first[i - 1]--;
		}
		res[i] = static_cast< char >((first[i] - '0') - (second[i] - '0')) + '0';
	}

	while (res[0] == '0' && res.length() != 1)
	{
		res.erase(0, 1);
	}

	return res;
}

MyString util::to_String(long long n)
{
	if (n == 0)
	{
		return MyString("0");
	}
	MyString res;
	while (n)
	{
		res.push_back(char(n % 10 + '0'));
		n /= 10;
	}
	return res;
}

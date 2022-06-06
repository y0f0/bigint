#include "util.h"

bool util::is_10_degree(const std::string& str)
{
	if (str[0] != '1')
		return false;
	for (size_t i = 1; i < str.size(); i++)
		if (str[i] != '0')
			return false;

	return true;
}

std::string util::multiply(std::string first, std::string second)
{
	if (first.length() > second.length())
		first.swap(second);

	std::string res = "0";
	for (int i = first.length() - 1; i >= 0; --i)
	{
		std::string temp = second;
		int currentDigit = first[i] - '0';
		int carry = 0;

		for (int j = temp.length() - 1; j >= 0; --j)
		{
			temp[j] = ((temp[j] - '0') * currentDigit) + carry;

			if (temp[j] > 9)
			{
				carry = (temp[j] / 10);
				temp[j] -= (carry * 10);
			}
			else
				carry = 0;

			temp[j] += '0';
		}

		if (carry > 0)
			temp.insert(0, 1, (carry + '0'));

		temp.append((first.length() - i - 1), '0');

		res = add(res, temp);
	}

	while (res[0] == '0' && res.length() != 1)
		res.erase(0, 1);

	return res;
}

std::string util::add(std::string first, std::string second)
{
	std::string add = (first.length() > second.length()) ? first : second;
	char carry = '0';
	int differenceInLength = std::abs((int)(first.size() - second.size()));

	if (first.size() > second.size())
	{
		second.insert(0, differenceInLength, '0');
	}

	else
	{
		first.insert(0, differenceInLength, '0');
	}

	for (int i = first.size() - 1; i >= 0; --i)
	{
		add[i] = ((carry - '0') + (first[i] - '0') + (second[i] - '0')) + '0';

		if (i != 0)
		{
			if (add[i] > '9')
			{
				add[i] -= 10;
				carry = '1';
			}
			else
				carry = '0';
		}
	}
	if (add[0] > '9')
	{
		add[0] -= 10;
		add.insert(0, 1, '1');
	}
	return add;
}

std::string util::subtract(std::string first, std::string second)
{
	std::string sub = (first.length() > second.length()) ? first : second;
	int differenceInLength = std::abs((int)(first.size() - second.size()));

	if (first.size() > second.size())
	{
		second.insert(0, differenceInLength, '0');
	}
	else
	{
		first.insert(0, differenceInLength, '0');
	}

	for (int i = first.length() - 1; i >= 0; --i)
	{
		if (first[i] < second[i])
		{
			first[i] += 10;
			first[i - 1]--;
		}
		sub[i] = ((first[i] - '0') - (second[i] - '0')) + '0';
	}

	while (sub[0] == '0' && sub.length() != 1)
	{
		sub.erase(0, 1);
	}

	return sub;
}

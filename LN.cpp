#include "LN.h"

void LN::remove_leading_zero(std::string& str)	  // should be in util, but didn't work
{
	size_t i;
	for (i = 0; i < str.size(); i++)
		if (str[i] != '0')
			break;

	if (i == str.size())
		str = "0";
	else
		str = str.substr(i);
}

std::pair< LN, LN > LN::divide(const LN& numerator, const LN& denominator) const
{
	LN copy = denominator;
	LN integrate_part = LN(1LL);

	while (copy < numerator)
	{
		integrate_part = integrate_part + LN(1LL);
		copy = copy + denominator;
	}
	LN remainder_part;
	if (copy > numerator)
	{
		integrate_part = integrate_part - LN(1LL);
		remainder_part = numerator - (copy - denominator);
	}

	return std::make_tuple(integrate_part, remainder_part);
}

LN& LN::operator=(const LN& other)	  // assignment copy
{
	sign = other.sign;
	number = other.number;
	return *this;
}

LN& LN::operator=(LN&& tmp) noexcept	// assignment move
{
	sign = tmp.sign;
	number = tmp.number;
	tmp.number.clear();
	return *this;
}

LN::LN(const std::string_view& sv) : LN{ std::string(sv.begin(), sv.end()) }
{
	if (sv == "NaN")
	{
		isNan = true;
	}
}

LN::LN(const std::string& s)
{
	if (s == "NaN")
	{
		isNan = true;
	}

	if (s[0] == '-')
	{
		number = s.substr(1);
		sign = s[0];
	}
	else
	{
		number = s;
		sign = '+';
	}
	size_t i;
	for (i = 0; i < number.size(); i++)
		if (number[i] != '0')
			break;

	if (i == s.size())
		number = "0";
	else
		number = number.substr(i);
}

LN LN::operator+(const LN& ln) const
{
	LN result;
	if (sign == ln.sign)
	{
		result.sign = sign;
		result.number = util::add(number, ln.number);
	}
	else
	{
		if (abs(*this) > abs(ln))
		{
			result.sign = sign;
			result.number = util::subtract(number, ln.number);
		}
		else
		{
			result.sign = ln.sign;
			result.number = util::subtract(ln.number, number);
		}
	}
	if (result.number == "0")	 // -0
		result.sign = '+';

	return result;
}

LN LN::operator-(const LN& ln) const
{
	LN copy(ln);
	copy.sign = copy.sign == this->sign ? '+' : '-';
	return (*this) + copy;
}

LN LN::operator*(const LN& ln) const
{
	LN mul;
	mul.number = util::multiply(number, ln.number);
	mul.sign = ln.sign == this->sign ? '+' : '-';

	if (mul.number == "0")
	{
		mul.sign = '+';
	}

	return mul;
}

LN LN::operator/(const LN& num) const
{
	LN numerator = abs(*this);
	LN denominator = abs(num);

	if (num == LN(0LL))
	{
		return NaN();
	}
	if (numerator < denominator)
		return LN(0LL);
	if (num == LN(1LL))
		return *this;
	if (num == LN(-1LL))
		return -(*this);

	LN result;
	if (numerator <= LN(LLONG_MAX) and denominator <= LN(LLONG_MAX))
	{
		long long quotientLL = std::stoll(numerator.number) / std::stoll(denominator.number);
		result = LN(quotientLL);
	}
	else if (numerator == denominator)
	{
		result = LN(1LL);
	}
	else if (util::is_10_degree(denominator.number))	// 10's optimizers
	{
		result.number = numerator.number.substr(0, numerator.number.size() - denominator.number.size() + 1);
	}
	else
	{
		result.number = "";
		LN part, part_total, remainder;
		size_t count = 0;
		remainder.number = numerator.number.substr(count, denominator.number.size() - 1);
		count = denominator.number.size() - 1;
		while (count < numerator.number.size())
		{
			part.number = remainder.number.append(1, numerator.number[count]);
			count++;
			while (part < denominator)
			{
				result.number += "0";
				if (count < numerator.number.size())
				{
					part.number.append(1, numerator.number[count]);
					count++;
				}
				else
					break;
			}
			if (part == denominator)
			{
				result.number += "1";
				remainder = LN(0LL);
			}
			else if (part > denominator)
			{
				remove_leading_zero(part.number);
				auto p = divide(part, denominator);
				remainder = p.first;
				part_total = p.second;
				result.number = result.number + part_total.number;
			}
			if (count > 3) {
				break;
			}
		}
	}
	remove_leading_zero(result.number);

	result.sign = this->sign == num.sign ? '+' : '-';
	return result;
}

LN LN::operator%(const LN& num) const
{
	LN numerator = abs(*this);
	LN denominator = abs(num);

	if (denominator == LN(0LL))
	{
		return NaN();
	}
	if (denominator == LN(1LL) || denominator == numerator)
		return LN(0LL);

	LN result;
	if (numerator <= LN(LLONG_MAX) && denominator <= LN(LLONG_MAX))
	{
		long long remainderLL = std::stoll(numerator.number) % std::stoll(denominator.number);
		result = LN(remainderLL);
	}
	else if (numerator < denominator)
	{
		result = numerator;
	}
	else if (util::is_10_degree(num.number))
	{
		result.number = numerator.number.substr(numerator.number.size() - num.number.size() - 1);
	}
	else
	{
		LN integrate_part = numerator / denominator;
		LN x = integrate_part * denominator;
		result = numerator - x;
	}
	remove_leading_zero(result.number);

	result.sign = this->sign;
	if (result.number == "0")
		result.sign = '+';

	return result;
}

bool LN::operator<(const LN& ln) const
{
	if (ln.sign == sign)
	{
		if (sign == '+')
		{
			if (number.length() == ln.number.length())
			{
				return number < ln.number;
			}
			return number.length() < ln.number.length();
		}
		return -(*this) > -ln;
	}
	return sign == '-';
}

LN LN::operator-() const
{
	LN res(number);
	if (number != "0")
	{
		if (sign == '+')
			res.sign = '-';
		else
			res.sign = '+';
	}

	return res;
}

LN LN::operator~() const
{
	if (*this < 0)
	{
		return NaN();
	}

	if (*this == ZERO())
		return ZERO();
	else if (*this < LN(4LL))
		return ONE();
	else if (*this < LN(9LL))
		return LN(2LL);
	else if (*this < 16)
		return LN(3LL);

	LN x = *this;
	LN root = ZERO();

	while (true)
	{
		root = (x + (*this / x)) / LN(2LL);
		LN diff = root - x;
		LN absolut = abs(diff);
		bool b = absolut < LN(1LL);
		if (absolut < LN(1LL))
		{
			break;
		}
		x = root;
	}
	return root;
}

std::ostream& operator<<(std::ostream& out, const LN& ln)
{
	if (ln.sign == '-')
	{
		out << '-';
	}
	out << ln.number;
	return out;
}

LN::operator long long() const
{
	try
	{
		return std::stoll(this->number);
	} catch (std::bad_alloc const &)
	{
		throw "Error: not enough memory for conversation to long long";
	}
}

// TODO: duplicates
LN& LN::operator%=(const LN& ln)
{
	if (anyIsNaN(*this, ln))
	{
		LN NaN = LN("NaN", '+', true);
		return NaN;
	}
	*this = *this % ln;

	return *this;
}
LN& LN::operator/=(const LN& ln)
{
	if (anyIsNaN(*this, ln))
	{
		LN NaN = LN("NaN", '+', true);
		return NaN;
	}
	*this = *this / ln;

	return *this;
}
LN& LN::operator*=(const LN& ln)
{
	if (anyIsNaN(*this, ln))
	{
		LN NaN = LN("NaN", '+', true);
		return NaN;
	}
	*this = *this * ln;

	return *this;
}
LN& LN::operator-=(const LN& ln)
{
	if (anyIsNaN(*this, ln))
	{
		LN NaN = LN("NaN", '+', true);
		return NaN;
	}
	*this = *this - ln;

	return *this;
}
LN& LN::operator+=(const LN& ln)
{
	if (anyIsNaN(*this, ln))
	{
		LN NaN = LN("NaN", '+', true);
		return NaN;
	}
	*this = *this + ln;

	return *this;
}
LN LN::operator++(int)
{
	if (this->isNan)
	{
		return *this;
	}

	LN temp = *this + LN(1LL);

	return temp;
}
LN& LN::operator--()
{
	if (this->isNan)
	{
		return *this;
	}
	*this -= LN(1LL);

	return *this;
}
LN LN::operator--(int)
{
	if (this->isNan)
	{
		return *this;
	}
	LN temp = *this;
	*this -= LN(1LL);

	return temp;
}
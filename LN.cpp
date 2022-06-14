#include "LN.h"

#include "String.h"

#include <climits>
#include <stdexcept>

void LN::remove_leading_zero(String& str)	 // should be in util, but didn't work
{
	size_t i;
	for (i = 0; i < str.size(); i++)
		if (str[i] != '0')
			break;

	if (i == str.size())
	{
		str = String("0");
	}
	else
	{
		str = str.substr(i);
	}
}

util::pair< LN, LN > LN::divide(const LN& numerator, const LN& denominator)
{
	LN copy = denominator;
	LN integrate_part = LN(1LL);

	while (copy < numerator)
	{
		integrate_part = integrate_part + LN(1LL);
		copy = copy + denominator;
	}
	LN remainder_part = LN(0LL);
	if (copy > numerator)
	{
		integrate_part = (integrate_part - LN(1LL));
		remainder_part = numerator - (copy - denominator);
	}
	return { integrate_part, remainder_part };
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
	number = std::move(tmp.number);
	return *this;
}

LN::LN(const std::string_view& sv) : LN{ String(sv.data()) }
{
	isNan = sv == "NaN";
}

LN::LN(const String& s)
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
	for (i = 0; i < number.length(); i++)
		if (number[i] != '0')
			break;

	if (i == s.length())
	{
		number = String("0");
	}
	else
	{
		number = number.substr(i);
	}
}

LN LN::operator+(const LN& ln) const
{
	if (ln.isNan || this->isNan)
	{
		return NaN();
	}
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
	if (result.number == "0")
	{	 // -0.in
		result.sign = '+';
	}

	return result;
}

LN LN::operator-(const LN& ln) const
{
	LN copy(ln);
	copy.sign = (copy.sign == '-') ? '+' : '-';
	return (*this) + copy;
}

LN LN::operator*(const LN& ln) const
{
	if (this->isNan || ln.isNan)
	{
		return NaN();
	}
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
	if (this->isNan || num.isNan)
	{
		return NaN();
	}
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
		return LN(-1LL) * (*this);

	LN result;
	if (numerator <= LN(LLONG_MAX) and denominator <= LN(LLONG_MAX))
	{
		long long quotientLL = stoll(numerator.number) / stoll(denominator.number);
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
		result.number = String("");
		LN part, part_total, remainder;
		size_t count = 0;
		remainder.number = numerator.number.substr(count, denominator.number.size() - 1);
		count = denominator.number.size() - 1;
		while (count < numerator.number.size())
		{
			remainder.number.append(1, numerator.number[count]);
			part.number = remainder.number;
			count++;
			while (part < denominator)
			{
				result.number += String("0");
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
				result.number += String("1");
				remainder = LN(0LL);
			}
			else if (part > denominator)
			{
				remove_leading_zero(part.number);
				auto p = divide(part, denominator);
				part_total = p.first;
				remainder = p.second;
				result.number = result.number + part_total.number;
			}
		}
	}
	remove_leading_zero(result.number);

	result.sign = this->sign == num.sign ? '+' : '-';
	return result;
}

LN LN::operator%(const LN& num) const
{
	if (this->isNan || num.isNan)
	{
		return NaN();
	}
	// n - (n // m) * m
	return *this - ((*this / num) * num);
}

bool LN::operator<(const LN& ln) const
{
	if (this->isNan || ln.isNan)
	{
		return false;
	}
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
		return LN(-1LL) * (*this) > LN(-1LL) * ln;
	}
	return sign == '-';
}

LN LN::operator~() const
{
	if (this->isNan || *this < 0)
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

LN operator"" _ln(unsigned long long x)
{
	if (x > LLONG_MAX)
	{
		throw std::runtime_error("Error: cannot cast to long long.");
	}
	return LN(x);
}

LN::operator long long() const
{
	try
	{
		return stoll(this->number);
	} catch (std::bad_alloc const &)
	{
		throw std::runtime_error("Error: not enough memory for conversation to long long");
	}
}

LN LN::operator%=(const LN& ln)
{
	if (anyIsNaN(*this, ln))
	{
		return LN::NaN();
	}
	*this = *this % ln;

	return *this;
}
LN LN::operator/=(const LN& ln)
{
	if (anyIsNaN(*this, ln))
	{
		return LN::NaN();
	}
	*this = *this / ln;

	return *this;
}
LN LN::operator*=(const LN& ln)
{
	if (anyIsNaN(*this, ln))
	{
		return LN::NaN();
	}
	*this = *this * ln;

	return *this;
}
LN LN::operator-=(const LN& ln)
{
	if (anyIsNaN(*this, ln))
	{
		return LN::NaN();
	}
	*this = *this - ln;

	return *this;
}
LN LN::operator+=(const LN& ln)
{
	if (anyIsNaN(*this, ln))
	{
		return LN::NaN();
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

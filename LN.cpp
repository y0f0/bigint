#include "LN.h"

#include "MyString.h"

#include <climits>
#include <new>

void LN::remove_leading_zero(MyString& str)	   // should be in util, but didn't work
{
	size_t i;
	for (i = 0; i < str.size(); i++)
		if (str[i] != '0')
			break;

	if (i == str.size())
	{
		str = MyString("0");
	}
	else
	{
		str = str.substr(i);
	}
}

util::pair< LN, LN > LN::divide(const LN& numerator, const LN& denominator)
{
	LN copy = denominator;
	LN integrate_part = ONE();

	while (copy < numerator)
	{
		integrate_part = integrate_part + ONE();
		copy = copy + denominator;
	}
	LN remainder_part = ZERO();
	if (copy > numerator)
	{
		integrate_part = (integrate_part - ONE());
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

LN::LN(const std::string_view& sv) : LN{ MyString(sv.data()) }
{
	isNan = sv == "NaN";
}

LN::LN(const MyString& s)
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
		number = MyString("0");
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

	if (num == ZERO())
	{
		return NaN();
	}
	if (numerator < denominator)
		return ZERO();
	if (num == ONE())
		return *this;
	if (num == MINUS_ONE())
		return MINUS_ONE() * (*this);

	LN result;
	result.number = MyString("");
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
			result.number += MyString("0");
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
			result.number += MyString("1");
			remainder = ZERO();
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
	//	}
	remove_leading_zero(result.number);

	result.sign = this->sign == num.sign ? '+' : '-';
	return result;
}

LN LN::operator%(const LN& num) const
{
	if (this->isNan || num.isNan || num == ZERO())
	{
		return NaN();
	}
	if (*this == ZERO())
	{
		return ZERO();
	}
	if (*this > ZERO() && num > ZERO())
	{
		return *this - ((*this / num) * num);
	}
	if (*this < ZERO() && num < ZERO())
	{
		return -(-*this - ((-*this / -num) * -num));
	}
	if (*this > ZERO() && num < ZERO())
	{
		LN div_up = (*this + (-num - ONE())) / -num;
		return *this - (-div_up * num);
	}
	LN div_up = (*this + (-num - ONE())) / -num;
	return *this - (-div_up * num);
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

	LN two(2LL);
	LN prev = *this / two;
	if (prev != ZERO())
	{
		LN current = (prev + *this / prev) / two;

		while (current < prev)
		{
			prev = current;
			current = (prev + *this / prev) / two;
		}

		return prev;
	}
	else
	{
		return *this;
	}
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
		throw std::bad_alloc();
	}
	return LN(x);
}

LN::operator long long() const
{
	try
	{
		return stoll(this->number);
	} catch (...)
	{
		throw std::bad_alloc();
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

	LN temp = *this + ONE();

	return temp;
}
LN& LN::operator--()
{
	if (this->isNan)
	{
		return *this;
	}
	*this -= ONE();

	return *this;
}
LN LN::operator--(int)
{
	if (this->isNan)
	{
		return *this;
	}
	LN temp = *this;
	*this -= ONE();

	return temp;
}

int comparing(const LN& lhs, const LN& rhs)
{
	if (lhs.sign == rhs.sign && lhs.number == rhs.number)
	{
		return 0;
	}
	if (lhs.sign == rhs.sign)
	{
		if (lhs.sign == '+')
		{
			if (lhs.number.length() == rhs.number.length())
			{
				return lhs.number < rhs.number ? -1 : 1;
			}
			return lhs.number.length() < rhs.number.length() ? -1 : 1;
		}
		return LN::MINUS_ONE() * lhs > LN::MINUS_ONE() * rhs ? -1 : 1;
	}
	return lhs.sign == '-' ? -1 : 1;
}

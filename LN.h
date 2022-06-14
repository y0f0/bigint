#pragma once

#include "String.h"
#include "util.h"

#include <iostream>
#include <limits>
#include <new>

class LN
{
  private:
	String number;
	char sign;
	bool isNan;

	static bool anyIsNaN(const LN& lhs, const LN& rhs) { return lhs.isNan || rhs.isNan; }

	static LN ZERO() { return LN(0LL); }
	static LN ONE() { return LN(1LL); }
	static LN MINUS_ONE() { return LN(-1LL); }
	static LN NaN() { return { String("NaN"), '+', true }; }

	static LN abs(const LN& ln) { return ln < 0 ? LN(-1LL) * ln : ln; }
	static LN abs(LN& ln) { return ln < 0 ? LN(-1LL) * ln : ln; }
	static void remove_leading_zero(String& str);
	[[nodiscard]] static util::pair< LN, LN > divide(const LN& dividend, const LN& divisor);

  public:
	LN operator++(int);
	LN& operator--();
	LN operator--(int);

	LN(String number, char sign, bool naNable) :
		number{ std::move(number) }, sign{ sign }, isNan{ naNable } {}				 // copy constructor
	LN(const LN& ln) : number{ ln.number }, sign{ ln.sign }, isNan{ ln.isNan } {}	 // copy constructor
	explicit LN(const long long& ll = 0) :
		number{ util::to_String(std::abs(ll)) }, sign{ ll < 0 ? '-' : '+' }, isNan{ false }
	{
	}
	explicit LN(const std::string_view& sv);
	explicit LN(const String& s);
	explicit LN(const char* cstring) : LN{ String(cstring) } {}
	LN(LN&& ln) noexcept : number(std::move(ln.number)), sign(ln.sign), isNan(ln.isNan) {}	  // move constructor
	LN& operator=(const LN&);																  // assignment copy
	LN& operator=(LN&& tmp) noexcept;														  // assignment move

	LN operator+(const LN&) const;
	LN operator-(const LN&) const;
	LN operator*(const LN&) const;
	LN operator/(const LN&) const;
	LN operator%(const LN&) const;

	LN operator+=(const LN& ln);
	LN operator-=(const LN& ln);
	LN operator*=(const LN& ln);
	LN operator/=(const LN& ln);
	LN operator%=(const LN& ln);

	bool operator<(const LN&) const;
	bool operator<=(const LN& ln) const { return !anyIsNaN(*this, ln) && (*this == ln || *this < ln); }
	bool operator>(const LN& ln) const { return !anyIsNaN(*this, ln) && !((*this < ln) || (*this == ln)); }
	bool operator>=(const LN& ln) const { return !anyIsNaN(*this, ln) && (*this == ln || *this > ln); }
	bool operator==(const LN& ln) const { return !anyIsNaN(*this, ln) && (sign == ln.sign && number == ln.number); }
	bool operator!=(const LN& ln) const { return anyIsNaN(*this, ln) || sign != ln.sign || number != ln.number; }

	bool operator<(const long long& ll) const { return *this < LN(ll); }
	bool operator<=(const long long& ll) const { return !(*this > LN(ll)); }

	LN operator~() const;

	explicit operator long long() const;
	explicit operator bool() const { return *this != ZERO(); }

	friend std::ostream& operator<<(std::ostream&, const LN&);
};

LN operator"" _ln(unsigned long long x);

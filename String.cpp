#include "String.h"

#include <algorithm>
#include <cstring>
#include <stdexcept>

String::String() : size_(1), capacity_(1)
{
	data_ = new char[1];
	data_[0] = '\0';
}

String::String(const char *cstr) : String()
{
	for (int i = 0; cstr[i] != '\0'; i++)
	{
		this->push_back(cstr[i]);
	}
}

String::String(int count, char ch) : size_(count + 1), capacity_(size_ * 2)
{
	data_ = new char[capacity_];
	while (count--)
	{
		data_[size_ - count - 2] = ch;
	}
	data_[size_ - 1] = '\0';
}

String::String(const String &string) : size_(string.size_), capacity_(string.capacity_)
{
	data_ = new char[capacity_];
	strncpy(data_, string.data_, string.size_);
	data_[size_ - 1] = '\0';
}

String::String(String &&string) noexcept : size_(string.size_), capacity_(string.capacity_), data_(string.data_)
{
	string.data_ = new char[1];
	string[0] = '\0';
	string.size_ = 1;
	string.capacity_ = 1;
}

String &String::operator=(const String &string)
{
	if (this->data_ == string.data_)
	{
		return *this;
	}
	delete[] data_;
	size_ = string.size_;
	capacity_ = string.capacity_;
	data_ = new char[capacity_];
	strncpy(data_, string.data_, capacity_);
	return *this;
}

String &String::operator=(String &string)
{
	if (this->data_ == string.data_)
	{
		return *this;
	}
	delete[] data_;
	size_ = string.size_;
	capacity_ = string.capacity_;
	data_ = new char[capacity_];
	strncpy(data_, string.data_, capacity_);
	return *this;
}

String &String::operator=(String &&string) noexcept
{
	if (this->data_ == string.data_)
	{
		return *this;
	}
	delete[] data_;
	size_ = string.size_;
	capacity_ = string.capacity_;
	data_ = string.data_;
	string.data_ = new char[1];
	string.data_[0] = '\0';
	string.size_ = 1;
	string.capacity_ = 1;
	return *this;
}

String::~String()
{
	delete[] data_;
}

int String::length() const
{
	return size_ - 1;
}

char &String::operator[](int i)
{
	return data_[i];
}

const char &String::operator[](int i) const
{
	return data_[i];
}

void String::reserve(int capacity)
{
	if (this->capacity_ >= capacity)
	{
		return;
	}
	capacity_ = capacity;
	char *new_str = new char[capacity_];
	strncpy(new_str, data_, size_);
	new_str[size_ - 1] = '\0';
	std::swap(new_str, data_);
	delete[] new_str;
}

void String::push_back(char ch)
{
	reserve(size_ + 1);
	size_++;
	data_[size_ - 2] = ch;
	data_[size_ - 1] = '\0';
}

void String::insert(int index, const String &string)
{
	reserve(size_ + string.length());
	for (int i = size_ - 2; i >= index; i--)
	{
		data_[i + string.length()] = data_[i];
	}
	for (int i = index; i < index + string.length(); i++)
	{
		data_[i] = string[i - index];
	}
	size_ = size_ + string.length();
	data_[size_ - 1] = '\0';
}

void String::insert(int index, const char *cstr)
{
	String in_str(cstr);
	in_str.size_ = 2;
	in_str.data_[1] = '\0';
	insert(index, in_str);
}

void String::erase(int index, int count)
{
	int actual = std::min(count, length() - index);
	for (int i = index; i < size_ - actual; i++)
	{
		data_[i] = data_[i + actual];
	}
	size_ = size_ - actual;
}

int String::compare(const String &string) const
{
	return strcmp(data_, string.data_);
}

int String::compare(const char *cstr) const
{
	return strcmp(data_, cstr);
}

String String::operator+(const String &string) const
{
	String res;
	res.reserve(size_ + string.length());
	strncpy(res.data_, data_, size_);
	strncpy(res.data_ + size_ - 1, string.data_, string.size_);
	res.size_ = size_ + string.length();
	return res;
}

String &String::operator+=(const String &string)
{
	reserve(size_ + string.length());
	strncpy(data_ + size_ - 1, string.data_, string.size_);
	size_ = size_ + string.length();
	return *this;
}

bool String::operator<(const String &string) const
{
	return compare(string) < 0;
}

bool String::operator>(const String &string) const
{
	return compare(string) > 0;
}

bool String::operator==(const String &string) const
{
	return compare(string) == 0;
}

bool String::operator!=(const String &string) const
{
	return compare(string) != 0;
}

bool String::operator<(const char *cstr) const
{
	return compare(cstr) < 0;
}

bool String::operator>(const char *cstr) const
{
	return compare(cstr) > 0;
}

bool String::operator==(const char *cstr) const
{
	return compare(cstr) == 0;
}

bool String::operator!=(const char *cstr) const
{
	return compare(cstr) != 0;
}

bool operator<(const char *lhs, const String &rhs)
{
	return rhs > lhs;
}

bool operator>(const char *lhs, const String &rhs)
{
	return rhs < lhs;
}

bool operator==(const char *lhs, const String &rhs)
{
	return rhs == lhs;
}

bool operator!=(const char *lhs, const String &rhs)
{
	return rhs != lhs;
}
long long stoll(String &string)
{
	long long res = 0;
	for (int i = string.capacity_; i >= 0; i--)
	{
		res += 10 * (string[i] - '0');
	}
	return res;
}

long long stoll(const String &string)
{
	long long res = 0;
	for (int i = string.capacity_; i >= 0; i--)
	{
		res += 10 * (string[i] - '0');
	}
	return res;
}
std::ostream &operator<<(std::ostream &out, const String &str)
{
	for (int i = 0; i < str.size_ - 1; i++)
	{
		if (str[i] != '\0')
		{
			out << str[i];
		}
		else
		{
			break;
		}
	}
	return out;
}
void String::insert(int index, const char *cstr, int count)
{
	String in_str(cstr);
	in_str.size_ = count + 1;
	in_str.data_[count] = '\0';
	insert(index, in_str);
}

String String::substr(int pos) const
{
	if (pos < 0)
	{
		throw std::runtime_error("Error: position is less the zero.");
	}
	String res;
	for (int i = pos; i < length(); i++)
	{
		res.push_back(data_[i]);
	}
	return res;
}

String String::substr(size_t pos, size_t len) const
{
	if (pos < 0 || len < 0)
	{
		throw std::runtime_error("Error: position or len is less the zero.");
	}
	String res;
	for (size_t i = pos; i < pos + len; i++)
	{
		res.push_back(data_[i]);
	}
	return res;
}

void String::append(int n, char ch)
{
	for (int i = 0; i < n; i++)
	{
		push_back(ch);
	}
}

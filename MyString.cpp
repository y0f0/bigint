#include "MyString.h"

#include <cstddef>
#include <cstring>
#include <fstream>
#include <stdexcept>

MyString::MyString() : size_(1), capacity_(1)
{
	data_ = new char[1];
	data_[0] = '\0';
}

MyString::MyString(const char *cstr) : MyString()
{
	for (int i = 0; cstr[i] != '\0'; i++)
	{
		this->push_back(cstr[i]);
	}
}

MyString::MyString(int count, char ch) : size_(count + 1), capacity_(size_ * 2)
{
	data_ = new char[capacity_];
	while (count--)
	{
		data_[size_ - count - 2] = ch;
	}
	data_[size_ - 1] = '\0';
}

MyString::MyString(const MyString &string) : size_(string.size_), capacity_(string.capacity_)
{
	data_ = new char[capacity_];
	strncpy(data_, string.data_, string.size_);
	data_[size_ - 1] = '\0';
}

MyString::MyString(MyString &&string) noexcept : size_(string.size_), capacity_(string.capacity_), data_(string.data_)
{
	string.data_ = new char[1];
	string[0] = '\0';
	string.size_ = 1;
	string.capacity_ = 1;
}

MyString &MyString::operator=(const MyString &string)
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

MyString &MyString::operator=(MyString &string)
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

MyString &MyString::operator=(MyString &&string) noexcept
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

MyString::~MyString()
{
	delete[] data_;
}

int MyString::length() const
{
	return size_ - 1;
}

char &MyString::operator[](int i)
{
	return data_[i];
}

const char &MyString::operator[](int i) const
{
	return data_[i];
}

void MyString::reserve(int capacity)
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

void MyString::push_back(char ch)
{
	reserve(size_ + 1);
	size_++;
	data_[size_ - 2] = ch;
	data_[size_ - 1] = '\0';
}

void MyString::insert(int index, const MyString &string)
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

void MyString::insert(int index, const char *cstr)
{
	MyString in_str(cstr);
	in_str.size_ = 2;
	in_str.data_[1] = '\0';
	insert(index, in_str);
}

void MyString::erase(int index, int count)
{
	int actual = std::min(count, length() - index);
	for (int i = index; i < size_ - actual; i++)
	{
		data_[i] = data_[i + actual];
	}
	size_ = size_ - actual;
}

int MyString::compare(const MyString &string) const
{
	return strcmp(data_, string.data_);
}

int MyString::compare(const char *cstr) const
{
	return strcmp(data_, cstr);
}

MyString MyString::operator+(const MyString &string) const
{
	MyString res;
	res.reserve(size_ + string.length());
	strncpy(res.data_, data_, size_);
	strncpy(res.data_ + size_ - 1, string.data_, string.size_);
	res.size_ = size_ + string.length();
	return res;
}

MyString &MyString::operator+=(const MyString &string)
{
	reserve(size_ + string.length());
	strncpy(data_ + size_ - 1, string.data_, string.size_);
	size_ = size_ + string.length();
	return *this;
}

bool MyString::operator<(const MyString &string) const
{
	return compare(string) < 0;
}

bool MyString::operator>(const MyString &string) const
{
	return compare(string) > 0;
}

bool MyString::operator==(const MyString &string) const
{
	return compare(string) == 0;
}

bool MyString::operator!=(const MyString &string) const
{
	return compare(string) != 0;
}

bool MyString::operator<(const char *cstr) const
{
	return compare(cstr) < 0;
}

bool MyString::operator>(const char *cstr) const
{
	return compare(cstr) > 0;
}

bool MyString::operator==(const char *cstr) const
{
	return compare(cstr) == 0;
}

bool MyString::operator!=(const char *cstr) const
{
	return compare(cstr) != 0;
}

bool operator<(const char *lhs, const MyString &rhs)
{
	return rhs > lhs;
}

bool operator>(const char *lhs, const MyString &rhs)
{
	return rhs < lhs;
}

bool operator==(const char *lhs, const MyString &rhs)
{
	return rhs == lhs;
}

bool operator!=(const char *lhs, const MyString &rhs)
{
	return rhs != lhs;
}
long long stoll(MyString &string)
{
	long long res = 0;
	long long power = 1;
	for (int i = string.length() - 1; i >= 0; i--)
	{
		res += power * (string[i] - '0');
		power *= 10;
	}
	return res;
}

long long stoll(const MyString &string)
{
	long long res = 0;
	for (int i = string.capacity_; i >= 0; i--)
	{
		res += 10 * (string[i] - '0');
	}
	return res;
}
std::ostream &operator<<(std::ostream &out, const MyString &str)
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
void MyString::insert(int index, const char *cstr, int count)
{
	MyString in_str(cstr);
	in_str.size_ = count + 1;
	in_str.data_[count] = '\0';
	insert(index, in_str);
}

MyString MyString::substr(int pos) const
{
	MyString res;
	for (int i = pos; i < length(); i++)
	{
		res.push_back(data_[i]);
	}
	return res;
}

MyString MyString::substr(size_t pos, size_t len) const
{
	MyString res;
	for (size_t i = pos; i < pos + len; i++)
	{
		res.push_back(data_[i]);
	}
	return res;
}

void MyString::append(int n, char ch)
{
	for (int i = 0; i < n; i++)
	{
		push_back(ch);
	}
}

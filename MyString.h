#pragma once
#include <cstddef>
#include <cstring>
#include <fstream>
#include <stdexcept>

class MyString
{
  public:
	MyString();
	explicit MyString(const char *);
	MyString(int, char);
	MyString(const MyString &);
	MyString(MyString &&) noexcept;
	MyString &operator=(const MyString &);
	MyString &operator=(MyString &);
	MyString &operator=(MyString &&) noexcept;
	~MyString();

	[[nodiscard]] int size() const { return length(); }
	[[nodiscard]] int length() const;

	char &operator[](int);
	const char &operator[](int) const;

	void push_back(char);
	void append(int n, char ch);

	void insert(int, const MyString &);
	void insert(int, const char *);
	void insert(int, const char *, int);

	void erase(int index, int count = 1);

	MyString operator+(const MyString &) const;
	MyString &operator+=(const MyString &);

	[[nodiscard]] MyString substr(size_t pos, size_t len) const;
	[[nodiscard]] MyString substr(int pos) const;

	bool operator<(const MyString &string) const;
	bool operator>(const MyString &string) const;
	bool operator==(const MyString &string) const;
	bool operator!=(const MyString &string) const;

	bool operator<(const char *cstr) const;
	bool operator>(const char *cstr) const;
	bool operator==(const char *cstr) const;
	bool operator!=(const char *cstr) const;

	friend bool operator<(const char *lhs, const MyString &rhs);
	friend bool operator>(const char *lhs, const MyString &rhs);
	friend bool operator==(const char *lhs, const MyString &rhs);
	friend bool operator!=(const char *lhs, const MyString &rhs);

	friend long long stoll(MyString &string);
	friend long long stoll(const MyString &string);

	friend std::ostream &operator<<(std::ostream &, const MyString &);

  private:
	int size_;
	int capacity_;
	char *data_;

	void reserve(int);

	[[nodiscard]] int compare(const MyString &) const;
	int compare(const char *) const;
};

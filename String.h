#pragma once
#include <cstddef>
#include <fstream>
#include <stdexcept>

class String
{
  public:
	String();
	explicit String(const char *);
	String(int, char);
	String(const String &);
	String(String &&) noexcept;
	String &operator=(const String &);
	String &operator=(String &);
	String &operator=(String &&) noexcept;
	~String();

	[[nodiscard]] int size() const { return length(); }
	[[nodiscard]] int length() const;

	char &operator[](int);
	const char &operator[](int) const;

	void push_back(char);
	void append(int n, char ch);

	void insert(int, const String &);
	void insert(int, const char *);
	void insert(int, const char *, int);

	void erase(int index, int count = 1);

	String operator+(const String &) const;
	String &operator+=(const String &);

	[[nodiscard]] String substr(size_t pos, size_t len) const;
	[[nodiscard]] String substr(int pos) const;

	bool operator<(const String &string) const;
	bool operator>(const String &string) const;
	bool operator==(const String &string) const;
	bool operator!=(const String &string) const;

	bool operator<(const char *cstr) const;
	bool operator>(const char *cstr) const;
	bool operator==(const char *cstr) const;
	bool operator!=(const char *cstr) const;

	friend bool operator<(const char *lhs, const String &rhs);
	friend bool operator>(const char *lhs, const String &rhs);
	friend bool operator==(const char *lhs, const String &rhs);
	friend bool operator!=(const char *lhs, const String &rhs);

	friend long long stoll(String &string);
	friend long long stoll(const String &string);

	friend std::ostream &operator<<(std::ostream &, const String &);

  private:
	int size_;
	int capacity_;
	char *data_;

	void reserve(int);

	[[nodiscard]] int compare(const String &) const;
	int compare(const char *) const;
};

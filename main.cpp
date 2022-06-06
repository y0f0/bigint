#include "LN.h"
#include "return_codes.h"
#include <unordered_map>

#include <fstream>
#include <functional>
#include <iostream>
#include <stack>
#include <string>
#include <utility>

int main(int argc, char* args[])
{
	if (argc != 3)
	{
		return ERROR_INVALID_PARAMETER;
	}
	std::ifstream in(args[1]);
	if (!in.is_open())
	{
		return ERROR_FILE_NOT_FOUND;
	};

	std::ofstream out(args[2]);
	if (!out.is_open() || !out.good())
	{
		return ERROR_FILE_EXISTS;
	}

	std::unordered_map< std::string, std::function< LN(LN, LN) > > binary_operations = {
		{ "+",
		  [](const LN& x, const LN& y) -> LN
		  {
			  return x + y;
		  } },
		{ "-",
		  [](const LN& x, const LN& y) -> LN
		  {
			  return x - y;
		  } },
		{ "*",
		  [](const LN& x, const LN& y) -> LN
		  {
			  return x * y;
		  } },
		{ "/",
		  [](const LN& x, const LN& y) -> LN
		  {
			  return x / y;
		  } },
		{ "%",
		  [](const LN& x, const LN& y) -> LN
		  {
			  return x % y;
		  } },
	};

	std::unordered_map< std::string, std::function< LN(LN) > > unary_operations = {
		{ "~",
		  [](const LN& x) -> LN
		  {
			  return ~x;
		  } },
		{ "_",
		  [](const LN& x) -> LN
		  {
			  return LN(-1LL) * x;
		  } },
	};

	std::unordered_map< std::string, std::function< bool(LN, LN) > > boolean_operations = {
		{ "<",
		  [](const LN& x, const LN& y) -> bool
		  {
			  return x < y;
		  } },
		{ "<=",
		  [](const LN& x, const LN& y) -> bool
		  {
			  return x <= y;
		  } },
		{ ">",
		  [](const LN& x, const LN& y) -> bool
		  {
			  return x > y;
		  } },
		{ ">=",
		  [](const LN& x, const LN& y) -> bool
		  {
			  return x >= y;
		  } },
		{ "==",
		  [](const LN& x, const LN& y) -> bool
		  {
			  return x == y;
		  } },
		{ "!=",
		  [](const LN& x, const LN& y) -> bool
		  {
			  return x != y;
		  } },
	};

	std::string line;
	std::stack< LN > data;

	while (in >> line)
	{
		try
		{
			if (binary_operations.count(line) && data.size() >= 2)
			{
				LN x = data.top();
				data.pop();
				LN y = data.top();
				data.pop();
				data.push(binary_operations[line](y, x));
			}
			else if (unary_operations.count(line) && !data.empty())
			{
				LN x = data.top();
				data.pop();
				data.push(unary_operations[line](x));
			}
			else if (boolean_operations.count(line) && data.size() >= 2)
			{
				LN x = data.top();
				data.pop();
				LN y = data.top();
				data.pop();
				out << boolean_operations[line](x, y) << '\n';
			}
			else if (line != "+" && line != "-" && line != "*" && line != "/" && line != "%" && line != "~" && line != "_" &&
					 line != "<" && line != "<=" && line != ">" && line != ">=" && line != "==" && line != "!=")
			{
				data.push(LN(std::string_view{ line }));
			}
		} catch (std::bad_alloc const &)
		{
			return ERROR_NOT_ENOUGH_MEMORY;
		} catch (const char* exception)
		{
			return ERROR_NOT_ENOUGH_MEMORY;
		} catch (std::exception const &)
		{
			return ERROR_UNKNOWN;
		}
	}
	while (!data.empty())
	{
		out << data.top();
		data.pop();
	}
	return ERROR_SUCCESS;
}
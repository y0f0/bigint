#pragma once

#include "LN.h"
#include "return_codes.h"
#include <unordered_map>

#include <fstream>
#include <functional>
#include <stack>
#include <string>

namespace operations
{
	std::unordered_map< std::string, std::function< LN(LN, LN) > > binary = {
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

	std::unordered_map< std::string, std::function< LN(LN) > > unary = {
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

	std::unordered_map< std::string, std::function< bool(LN, LN) > > boolean = {
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

}	 // namespace operations

int solve(std::istream& in, std::ostream& out)	  // encapsulation for testing
{
	std::string line;
	std::stack< LN > data;

	while (in >> line)
	{
		try
		{
			if (operations::binary.count(line) && data.size() >= 2)
			{
				LN x = data.top();
				data.pop();
				LN y = data.top();
				data.pop();
				data.push(operations::binary[line](y, x));
			}
			else if (operations::unary.count(line) && !data.empty())
			{
				LN x = data.top();
				data.pop();
				data.push(operations::unary[line](x));
			}
			else if (operations::boolean.count(line) && data.size() >= 2)
			{
				LN x = data.top();
				data.pop();
				LN y = data.top();
				data.pop();
				out << operations::boolean[line](y, x) << '\n';
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
		out << data.top() << '\n';
		data.pop();
	}
	return ERROR_SUCCESS;
}

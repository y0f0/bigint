#pragma once

#include "String.h"

namespace util
{
	bool is_10_degree(const String&);
	String add(String, String);
	String subtract(String, String);
	String multiply(String, String);
	String to_String(long long n);
	template< typename T1, typename T2 >
	struct pair
	{
		pair(T1 const & v1, T2 const & v2)	  // (1)
			:
			first(v1),
			second(v2)
		{
		}

		template< class U, class V >
		pair(U&& v1, V&& v2)	// (2)
			:
			first(std::forward< U >(v1)),
			second(std::forward< V >(v2))
		{
		}

		T1 first;
		T2 second;
	};
}	 // namespace util

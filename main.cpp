#include "return_codes.h"
#include "solve.h"

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
	}

	std::ofstream out(args[2]);
	if (!out.is_open() || !out.good())
	{
		return ERROR_FILE_EXISTS;
	}

	try
	{
		int ret = solve(in, out);
		if (ret != ERROR_SUCCESS)
		{
			return ret;
		}
	} catch (...)
	{
		return ERROR_UNKNOWN;
	}

	return ERROR_SUCCESS;
}
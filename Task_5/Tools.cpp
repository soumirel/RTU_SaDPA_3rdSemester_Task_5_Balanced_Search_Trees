#include "Tools.h"

int keyCmp(const char* left, const char* right)
{
	int left_day = (left[0] - '0') * 10 + (left[1] - '0');
	int left_month = (left[3] - '0') * 10 + (left[4] - '0');
	int right_day = (right[0] - '0') * 10 + (right[1] - '0');
	int right_month = (right[3] - '0') * 10 + (right[4] - '0');

	if (left_month < right_month)
	{
		return -1;
	}
	else if (left_month > right_month)
	{
		return 1;
	}
	else
	{
		if (left_day < right_day)
		{
			return -1;
		}
		else if (left_day > right_day)
		{
			return 1;
		}
		else
		{
			return 0;
		}
	}
}


int keyCmp(std::string left, std::string right)
{
	int left_day = (left[0] - '0') * 10 + (left[1] - '0');
	int left_month = (left[3] - '0') * 10 + (left[4] - '0');
	int right_day = (right[0] - '0') * 10 + (right[1] - '0');
	int right_month = (right[3] - '0') * 10 + (right[4] - '0');

	if (left_month < right_month)
	{
		return -1;
	}
	else if (left_month > right_month)
	{
		return 1;
	}
	else
	{
		if (left_day < right_day)
		{
			return -1;
		}
		else if (left_day > right_day)
		{
			return 1;
		}
		else
		{
			return 0;
		}
	}
}
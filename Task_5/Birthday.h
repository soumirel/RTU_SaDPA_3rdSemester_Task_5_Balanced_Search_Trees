#pragma once

#include <memory>

struct Birthday
{
	char key_date[6];
	char name[6];

	Birthday(const char* key_date, const char* name)
	{
		strcpy_s(this->key_date, key_date);
		strcpy_s(this->name, name);
	}

	Birthday()
	{
		key_date[5] = '\0';
		name[5] = '\0';
	}
};
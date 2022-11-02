#pragma once

#include <string>
#include <fstream>
#include "Birthday.h"

using namespace std;

class BinaryFile
{
public:
	BinaryFile() {}

	BinaryFile(string fileName);

	size_t getSize();

	const char* find(char* key);

	const char* at(size_t index);

	const char* keyAt(size_t index);

	void add(const char* key,
		const char* value,
		size_t index = 0);

	void print();

private:

	fstream file;

	string fileName;

	size_t size = 0;

	const string sourceFileName = "source.txt";

	void createFile();	

	void openFile();

	void closeFile();
};
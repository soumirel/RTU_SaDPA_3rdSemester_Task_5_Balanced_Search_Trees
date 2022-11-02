#include <iostream>
#include "BinaryFile.h"


BinaryFile::BinaryFile(string fileName)
{
	this->fileName = fileName + ".dat";
	
	file.open(this->fileName, ios::in | ios::out | ios::binary | ios::trunc);

	createFile();

	closeFile();
}


void BinaryFile::openFile()
{
	file.open(this->fileName, ios::in | ios:: out | ios::binary);
}


void BinaryFile::closeFile()
{
	file.close();
}


size_t BinaryFile::getSize()
{
	return size;
}


const char* BinaryFile::find(char* key)
{
	openFile();
	
	file.seekg(0, ios::beg);

	Birthday birthday;

	while (file.read((char*)&birthday, sizeof(Birthday)))
	{
		if (strcmp(birthday.key_date, key) == 0)
		{
			return birthday.name;
		}
	}

	return nullptr;

	closeFile();
}


const char* BinaryFile::at(size_t index)
{
	openFile();
	
	if (index > size)
	{
		closeFile();
		throw exception("Index out of range");
	}
	
	file.seekg(index * sizeof(Birthday), ios::beg);

	Birthday birthday;

	file.read((char*)&birthday, sizeof(Birthday));

	closeFile();

	return birthday.name;	
}


const char* BinaryFile::keyAt(size_t index)
{
	openFile();

	if (index > size)
	{
		throw exception("Index out of range");
	}

	file.seekg(index * sizeof(Birthday), ios::beg);

	Birthday birthday;

	if (file.read((char*)&birthday, sizeof(Birthday)))
	{
		closeFile();
		return birthday.key_date;
	}

	closeFile();

	return nullptr;
}


void BinaryFile::createFile()
{

	if (!file.is_open())
	{
		file.open(fileName, ios::in | ios::out | ios::binary | ios::trunc);
	}

	ifstream sourceFile(sourceFileName);

	Birthday birthday;

	while (!sourceFile.eof())
	{
		sourceFile >> birthday.key_date;
		sourceFile.get();
		sourceFile >> birthday.name;

		file.write((char*)&birthday, sizeof(Birthday));

		size++;
	}

	sourceFile.close();
}


void BinaryFile::add(const char* key,
	const char* value,
	size_t index)
{
	openFile();

	if (index > size)
	{
		closeFile();
		throw exception("Index out of range");
	}

	file.seekg(index * sizeof(Birthday), ios::beg);

	Birthday birthday(key, value);

	file.write((char*)&birthday, sizeof(Birthday));

	size++;

	closeFile();
}


void BinaryFile::print()
{
	openFile();

	file.seekg(0, ios::beg);

	Birthday birthday;

	while (file.read((char*)&birthday, sizeof(Birthday)))
	{
		cout << birthday.key_date << " " << birthday.name << '\n';
	}

	closeFile();
}
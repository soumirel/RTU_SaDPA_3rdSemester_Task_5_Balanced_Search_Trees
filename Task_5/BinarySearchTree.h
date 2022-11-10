#pragma once

#include "BinaryFile.h"
#include <memory>


class BinarySearchTree
{
public:
	BinarySearchTree();

	void add(char[], size_t);

	size_t find(const char*);

	void remove(const char*);

	void print();
	
private:
	struct Node
	{
		char key_date[6];
		size_t indexInFile;
		Node* left;
		Node* right;

		Node(const char* key_date, size_t indexInFile)
		{
			strcpy_s(this->key_date, key_date);
			this->indexInFile = indexInFile;
			left = nullptr;
			right = nullptr;
		}
	};

	Node* root;

	void add(Node*);

	void print(Node*, size_t);
};


class BinaryTreeManager
{
private:
	BinarySearchTree tree;
	BinaryFile* file;

public:
	BinaryTreeManager(BinaryFile*);

	void add(char[], size_t);
	void remove(char[]);
	string find(char[]);
	void print();
};


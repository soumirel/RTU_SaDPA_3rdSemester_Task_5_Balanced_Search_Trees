#pragma once

#include "BinaryFile.h"
#include <memory>

class BinarySearchTree
{
public:
	BinarySearchTree();

	BinarySearchTree(BinaryFile* file);

	void add(char key[], size_t indexInFile);

	size_t find(const char* key);

	void remove(const char* key);

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

	void add(Node* node);

	void print(Node* node, size_t level);
};


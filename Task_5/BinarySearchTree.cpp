#include "BinarySearchTree.h"
#include "Tools.h"
#include <iostream>

int keyCmp(const char* left, const char* right);


BinaryTreeManager::BinaryTreeManager(BinaryFile* file)
{
	this->file = file;
	tree = BinarySearchTree();
	int size = this->file->getSize();
	char currentKey[6];

	for (int i = 0; i < size; i++)
	{
		strcpy_s(currentKey, this->file->keyAt(i).c_str());
		tree.add(currentKey, i);
	}
}


void BinaryTreeManager::add(char key[], size_t index)
{
	tree.add(key, index);
}


void BinaryTreeManager::remove(char key[])
{
	tree.remove(key);
}


string BinaryTreeManager::find(char key[])
{	
	return file->at(tree.find(key));	
}


void BinaryTreeManager::print()
{
	tree.print();
}


BinarySearchTree::BinarySearchTree()
{
	root = nullptr;
}


void BinarySearchTree::add(char key[], size_t indexInFile)
{
	Node* node = new Node(key, indexInFile);
	add(node);
}


void BinarySearchTree::add(Node* node)
{
	if (root == nullptr)
	{
		root = node;
		return;
	}

	Node* current = root;
	Node* parent = nullptr;

	while (current != nullptr)
	{
		parent = current;

		if (keyCmp(node->key_date, current->key_date) < 0)
		{
			current = current->left;
		}
		else
		{
			current = current->right;
		}
	}

	if (keyCmp(node->key_date, parent->key_date) < 0)
	{
		parent->left = node;
	}
	else
	{
		parent->right = node;
	}
}


size_t BinarySearchTree::find(const char* key)
{
	Node* current = root;

	while (current != nullptr)
	{
		if (keyCmp(key, current->key_date) == 0)
		{
			return current->indexInFile;
		}
		else if (keyCmp(key, current->key_date) < 0)
		{
			current = current->left;
		}
		else
		{
			current = current->right;
		}
	}

	throw exception("Key not found");
}


void BinarySearchTree::remove(const char* key)
{
	Node* current = root;
	Node* parent = nullptr;

	while (current != nullptr)
	{
		if (keyCmp(key, current->key_date) == 0)
		{
			break;
		}
		else if (keyCmp(key, current->key_date) < 0)
		{
			parent = current;
			current = current->left;
		}
		else
		{
			parent = current;
			current = current->right;
		}
	}

	if (current == nullptr)
	{
		throw exception("Key not found");
	}

	if (current->left == nullptr && current->right == nullptr)
	{
		if (parent == nullptr)
		{
			root = nullptr;
		}
		else if (parent->left == current)
		{
			parent->left = nullptr;
		}
		else
		{
			parent->right = nullptr;
		}

		delete current;
	}
	else if (current->left == nullptr)
	{
		if (parent == nullptr)
		{
			root = current->right;
		}
		else if (parent->left == current)
		{
			parent->left = current->right;
		}
		else
		{
			parent->right = current->right;
		}

		delete current;
	}
	else if (current->right == nullptr)
	{
		if (parent == nullptr)
		{
			root = current->left;
		}
		else if (parent->left == current)
		{
			parent->left = current->left;
		}
		else
		{
			parent->right = current->left;
		}

		delete current;
	}
	else
	{
		Node* successor = current->right;
		Node* successorParent = current;

		while (successor->left != nullptr)
		{
			successorParent = successor;
			successor = successor->left;
		}

		if (successorParent != current)
		{
			successorParent->left = successor->right;
			successor->right = current->right;
		}

		successor->left = current->left;

		if (parent == nullptr)
		{
			root = successor;
		}
		else if (parent->left == current)
		{
			parent->left = successor;
		}
		else
		{
			parent->right = successor;
		}
	}
}


void BinarySearchTree::print()
{
	print(root, 0);
}


void BinarySearchTree::print(Node* node, size_t level)
{
	if (node != nullptr)
	{
		print(node->right, level + 1);
		for (size_t i = 0; i < level; i++)
		{
			cout << "       ";
		}
		cout << node->key_date << endl;
		print(node->left, level + 1);
	}
}

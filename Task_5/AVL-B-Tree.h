
#pragma once


#include <iostream>
#include <queue>
#include "Tools.h"
#include "BinaryFIle.h"


using namespace std;


class BTree 
{

    friend class BTreePrinter;

private:

    struct TreeNode 
    {

        struct NodeCell 
        {
            string key;
            size_t index;

            NodeCell()
            {
                this->key = "00.00";
                this->index = 0;
            }

            NodeCell(string k, size_t i)
            {
                this->key = k;
                this->index = i;
            }
        };

        friend class BTree;

        NodeCell* keyCells;
        int T;
        TreeNode** childrens;
        int size;
        bool isLeaf;

        TreeNode(int, bool);

        TreeNode* get(string);

		void remove(string);
		
    private:
        void insert(string, size_t);
		
        int findKeyIndex(string);

		void removeFromLeaf(int);

		void removeFromNonLeaf(int);

        void splitChild(int, TreeNode*);

		NodeCell getPredecessor(int);

		NodeCell getSuccessor(int);

		void fill(int);

		void borrowFromPrev(int);

		void borrowFromNext(int);

		void merge(int);
	};

    TreeNode* root;
    int T;


public:
    BTree(int treeParameter) 
    {
        root = NULL;
        T = treeParameter;
    }

    BTree()
    {
        root = NULL;
        T = 2;
    }
	
    size_t find(string);

    void add(string k, size_t i);

    void remove(string k);
};


class BTreePrinter
{
private:
    BTree* tree;
    int comparisonCount = 0;

public:
    BTreePrinter(BTree* tree) : tree(tree) {}
    BTreePrinter() { tree = new BTree(); }

    void print()
    {
        traverse(tree->root);
        comparisonCount = 0;
    }

private:
    void traverse(BTree::TreeNode* node)
    {
        std::queue<BTree::TreeNode*> queue;
        queue.push(node);
        while (!queue.empty())
        {
            BTree::TreeNode* current = queue.front();
            queue.pop();
            int i;
            for (i = 0; i < current->size; i++)
            {
                if (current->isLeaf == false)
                {
                    comparisonCount++;
                    queue.push(current->childrens[i]);
                }
                cout << " " << current->keyCells[i].key << " " << current->keyCells[i].index << endl;
            }
            if (current->isLeaf == false)
            {
                comparisonCount++;
                queue.push(current->childrens[i]);
            }
        }
    }
};


class BTreeManager
{
private:
    BTree tree;
    BinaryFile* file;
    BTreePrinter printer;

public:
    BTreeManager(BinaryFile*, int);

    void add(char[], size_t);
    void remove(char[]);
    string find(char[]);
    void print();
};
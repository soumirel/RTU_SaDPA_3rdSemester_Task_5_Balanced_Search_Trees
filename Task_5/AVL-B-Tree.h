
#pragma once


#include <iostream>
#include <queue>
#include "Tools.h"


using namespace std;


class BTree {

    friend class BTreePrinter;

private:
    struct TreeNode {
        string* keys;
        int t;
        TreeNode** C;
        int size;
        bool leaf;

        TreeNode(int, bool);

        void insertNotFull(string );

        void splitChild(int, TreeNode* );

        TreeNode* get(string);

		void remove(string);
		
    private:
        int findKeyIndex(string);

		void removeFromLeaf(int);

		void removeFromNonLeaf(int);

		string getPred(int);

		string getSucc(int);

		void fill(int);

		void borrowFromPrev(int);

		void borrowFromNext(int);

		void merge(int);
	};

    TreeNode* root;
    int t;

public:
    BTree(int temp) {
        root = NULL;
        t = temp;
    }
	

    TreeNode* get(string k) {
        return (root == NULL) ? NULL : root->get(k);
    }

    void insert(string k);

    void remove(string k);
};


class BTreePrinter
{
private:
    BTree* tree;
    int comparisonCount = 0;

public:
    BTreePrinter(BTree* tree) : tree(tree) {}

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
                if (current->leaf == false)
                {
                    comparisonCount++;
                    queue.push(current->C[i]);
                }
                cout << " " << current->keys[i] << endl;
            }
            if (current->leaf == false)
            {
                comparisonCount++;
                queue.push(current->C[i]);
            }
        }
    }
};
#include "AVL-B-Tree.h"


BTree::TreeNode::TreeNode(int t1, bool leaf1) {
    t = t1;
    leaf = leaf1;

    keys = new string[2 * t - 1];
    C = new TreeNode * [2 * t];

    size = 0;
}


BTree::TreeNode* BTree::TreeNode::get(string k) {
    int i = 0;
    while (i < size && keyCmp(k, keys[i]) > 0)
        i++;

    if (keyCmp(keys[i], k) == 0)
        return this;

    if (leaf == true)
        return NULL;

    return C[i]->get(k);
}

void BTree::insert(string k) {
    if (root == NULL) {
        root = new TreeNode(t, true);
        root->keys[0] = k;
        root->size = 1;
    }
    else {
        if (root->size == 2 * t - 1) {
            TreeNode* s = new TreeNode(t, false);

            s->C[0] = root;
            s->splitChild(0, root);

            int i = 0;
            if (keyCmp(s->keys[0], k) < 0)
                i++;
            s->C[i]->insertNotFull(k);

            root = s;
        }
        else
            root->insertNotFull(k);
    }
}


void BTree::TreeNode::insertNotFull(string k) {
    int i = size - 1;

    if (leaf == true) {
        while (i >= 0 && keyCmp(keys[i], k) > 0) {
            keys[i + 1] = keys[i];
            i--;
        }

        keys[i + 1] = k;
        size = size + 1;
    }
    else {
        while (i >= 0 && keyCmp(keys[i], k) > 0)
            i--;

        if (C[i + 1]->size == 2 * t - 1) {
            splitChild(i + 1, C[i + 1]);

            if (keyCmp(keys[i + 1], k) < 0)
                i++;
        }
        C[i + 1]->insertNotFull(k);
    }
}


void BTree::TreeNode::splitChild(int i, TreeNode* y) {
    TreeNode* z = new TreeNode(y->t, y->leaf);
    z->size = t - 1;

    for (int j = 0; j < t - 1; j++)
        z->keys[j] = y->keys[j + t];

    if (y->leaf == false) {
        for (int j = 0; j < t; j++)
            z->C[j] = y->C[j + t];
    }

    y->size = t - 1;
    for (int j = size; j >= i + 1; j--)
        C[j + 1] = C[j];

    C[i + 1] = z;

    for (int j = size - 1; j >= i; j--)
        keys[j + 1] = keys[j];

    keys[i] = y->keys[t - 1];
    size = size + 1;
}


void BTree::remove(string k) {
	if (!root) 
	{
		cout << "Удаление невозможно. Дерево пусто" << endl;
		return;
	}

	root->remove(k);

	if (root->size == 0) {
		TreeNode* tmp = root;
		if (root->leaf)
			root = NULL;
		else
			root = root->C[0];

		delete tmp;
	}
}


void BTree::TreeNode::remove(string k) {
	int index = findKeyIndex(k);

	if (index < size && keyCmp(keys[index], k) == 0) 
	{
		if (leaf)
		{
			removeFromLeaf(index);
		}
		else
		{
			removeFromNonLeaf(index);
		}
	}
	else {
		if (leaf) 
		{
			cout << "Ключа " << k << " нет в дереве" << endl;
			return;
		}

		bool flag = ((index == size) ? true : false);

		if (C[index]->size < t)
		{
			fill(index);
		}

		if (flag && index > size)
		{
			C[index - 1]->remove(k);
		}
		else
		{
			C[index]->remove(k);
		}
	}
}


int BTree::TreeNode::findKeyIndex(string k)
{
	int index = 0;
	while (index < size && keyCmp(keys[index], k) < 0)
	{
		++index;
	}
		
	return index;
}


void BTree::TreeNode::removeFromLeaf(int index) 
{
	for (int i = index + 1; i < size; ++i)
	{
		keys[i - 1] = keys[i];
	}	

	size--;
}


void BTree::TreeNode::removeFromNonLeaf(int index) 
{
	string k = keys[index];

	if (C[index]->size >= t) 
	{
		string pred = getPred(index);
		keys[index] = pred;
		C[index]->remove(pred);
	}
	else if (C[index + 1]->size >= t) 
	{
		string succ = getSucc(index);
		keys[index] = succ;
		C[index + 1]->remove(succ);
	}
	else {
		merge(index);
		C[index]->remove(k);
	}
}


string BTree::TreeNode::getPred(int index) 
{
	TreeNode* cur = C[index];
	while (!cur->leaf)
	{
		cur = cur->C[cur->size];
	}
		
	return cur->keys[cur->size - 1];
}


string BTree::TreeNode::getSucc(int index) 
{
	TreeNode* cur = C[index + 1];
	while (!cur->leaf)
	{
		cur = cur->C[0];
	}

	return cur->keys[0];
}


void BTree::TreeNode::fill(int index) 
{
	if (index != 0 && C[index - 1]->size >= t)
	{
		borrowFromPrev(index);
	}	
	else if (index != size && C[index + 1]->size >= t)
	{
		borrowFromNext(index);
	}
	else 
	{
		if (index != size)
		{
			merge(index);
		}	
		else
		{
			merge(index - 1);
		}	
	}
}


void BTree::TreeNode::borrowFromPrev(int inedx) 
{
	TreeNode* child = C[inedx];
	TreeNode* sibling = C[inedx - 1];

	for (int i = child->size - 1; i >= 0; --i)
	{
		child->keys[i + 1] = child->keys[i];
	}		

	if (!child->leaf) 
	{
		for (int i = child->size; i >= 0; --i)
		{
			child->C[i + 1] = child->C[i];
		}			
	}

	child->keys[0] = keys[inedx - 1];

	if (!child->leaf)
	{
		child->C[0] = sibling->C[sibling->size];
	}

	keys[inedx - 1] = sibling->keys[sibling->size - 1];

	child->size++;
	sibling->size--;
}


void BTree::TreeNode::borrowFromNext(int index) 
{
	TreeNode* child = C[index];
	TreeNode* sibling = C[index + 1];

	child->keys[(child->size)] = keys[index];

	if (!(child->leaf))
	{
		child->C[(child->size) + 1] = sibling->C[0];
	}

	keys[index] = sibling->keys[0];

	for (int i = 1; i < sibling->size; ++i)
	{
		sibling->keys[i - 1] = sibling->keys[i];
	}

	if (!sibling->leaf) 
	{
		for (int i = 1; i <= sibling->size; ++i)
		{
			sibling->C[i - 1] = sibling->C[i];
		}
	}

	child->size++;
	sibling->size--;
}


void BTree::TreeNode::merge(int index) 
{
	TreeNode* child = C[index];
	TreeNode* sibling = C[index + 1];

	child->keys[t - 1] = keys[index];

	for (int i = 0; i < sibling->size; ++i)
	{
		child->keys[i + t] = sibling->keys[i];
	}

	if (!child->leaf) 
	{
		for (int i = 0; i <= sibling->size; ++i)
		{
			child->C[i + t] = sibling->C[i];
		}
	}

	for (int i = index + 1; i < size; ++i)
	{
		keys[i - 1] = keys[i];
	}

	for (int i = index + 2; i <= size; ++i)
	{
		C[i - 1] = C[i];
	}

	child->size += sibling->size + 1;
	size--;

	delete(sibling);
}
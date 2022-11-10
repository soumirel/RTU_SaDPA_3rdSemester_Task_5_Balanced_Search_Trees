#include "AVL-B-Tree.h"


BTreeManager::BTreeManager(BinaryFile* file, int T)
{
	this->file = file;
	tree = BTree(T);
	printer = BTreePrinter(&tree);
	int size = this->file->getSize();
	char currentKey[6];

	for (int i = 0; i < size; i++)
	{
		strcpy_s(currentKey, this->file->keyAt(i).c_str());
		tree.add(currentKey, i);
	}
}


void BTreeManager::add(char key[], size_t index)
{
	tree.add(key, index);
}


void BTreeManager::remove(char key[])
{
	tree.remove(key);
}


string BTreeManager::find(char key[])
{
	return file->at(tree.find(key));
}


void BTreeManager::print()
{
	printer.print();
}


BTree::TreeNode::TreeNode(int t, bool leaf) {
    T = t;
    isLeaf = leaf;

    keyCells = new NodeCell[2 * T - 1];
    childrens = new TreeNode * [2 * T];

    size = 0;
}


size_t BTree::find(string k)
{
	BTree::TreeNode* node = root->get(k);
	for (int i = 0; i < node->size; i++)
	{
		if (keyCmp(k, node->keyCells[i].key) == 0)
		{
			return node->keyCells[i].index;
		}
	}
}


BTree::TreeNode* BTree::TreeNode::get(string k) 
{
    int i = 0;
    while (i < size && keyCmp(k, keyCells[i].key) > 0)
        i++;

    if (keyCmp(keyCells[i].key, k) == 0)
        return this;

    if (isLeaf == true)
        return NULL;

    return childrens[i]->get(k);
}

void BTree::add(string k, size_t ind) 
{
    if (root == NULL) {
        root = new TreeNode(T, true);
        root->keyCells[0] = 
			BTree::TreeNode::NodeCell(k, ind);
        root->size = 1;
    }
    else {
        if (root->size == 2 * T - 1) {
            TreeNode* s = new TreeNode(T, false);

            s->childrens[0] = root;
            s->splitChild(0, root);

            int i = 0;
            if (keyCmp(s->keyCells[0].key, k) < 0)
                i++;
            s->childrens[i]->insert(k, ind);

            root = s;
        }
        else
            root->insert(k, ind);
    }
}


void BTree::TreeNode::insert(string k, size_t ind) 
{
    int i = size - 1;

    if (isLeaf == true) {
        while (i >= 0 && keyCmp(keyCells[i].key, k) > 0) {
            keyCells[i + 1] = keyCells[i];
            i--;
        }

        keyCells[i + 1] = BTree::TreeNode::NodeCell(k, ind);
        size = size + 1;
    }
    else {
        while (i >= 0 && keyCmp(keyCells[i].key, k) > 0)
            i--;

        if (childrens[i + 1]->size == 2 * T - 1) {
            splitChild(i + 1, childrens[i + 1]);

            if (keyCmp(keyCells[i + 1].key, k) < 0)
                i++;
        }
        childrens[i + 1]->insert(k, ind);
    }
}


void BTree::TreeNode::splitChild(int i, TreeNode* y) 
{
    TreeNode* z = new TreeNode(y->T, y->isLeaf);
    z->size = T - 1;

    for (int j = 0; j < T - 1; j++)
        z->keyCells[j] = y->keyCells[j + T];

    if (y->isLeaf == false) {
        for (int j = 0; j < T; j++)
            z->childrens[j] = y->childrens[j + T];
    }

    y->size = T - 1;
    for (int j = size; j >= i + 1; j--)
        childrens[j + 1] = childrens[j];

    childrens[i + 1] = z;

    for (int j = size - 1; j >= i; j--)
        keyCells[j + 1] = keyCells[j];

    keyCells[i] = y->keyCells[T - 1];
    size = size + 1;
}


void BTree::remove(string k) 
{
	if (!root) 
	{
		cout << "Удаление невозможно. Дерево пусто" << endl;
		return;
	}

	root->remove(k);

	if (root->size == 0) {
		TreeNode* tmp = root;
		if (root->isLeaf)
			root = NULL;
		else
			root = root->childrens[0];

		delete tmp;
	}
}


void BTree::TreeNode::remove(string k) 
{
	int index = findKeyIndex(k);

	if (index < size && keyCmp(keyCells[index].key, k) == 0) 
	{
		if (isLeaf)
		{
			removeFromLeaf(index);
		}
		else
		{
			removeFromNonLeaf(index);
		}
	}
	else {
		if (isLeaf) 
		{
			cout << "Ключа " << k << " нет в дереве" << endl;
			return;
		}

		bool isNodeFull = ((index == size) ? true : false);

		if (childrens[index]->size < T)
		{
			fill(index);
		}

		if (isNodeFull && index > size)
		{
			childrens[index - 1]->remove(k);
		}
		else
		{
			childrens[index]->remove(k);
		}
	}
}


int BTree::TreeNode::findKeyIndex(string k)
{
	int index = 0;
	while (index < size && keyCmp(keyCells[index].key, k) < 0)
	{
		++index;
	}
		
	return index;
}


void BTree::TreeNode::removeFromLeaf(int index) 
{
	for (int i = index + 1; i < size; ++i)
	{
		keyCells[i - 1] = keyCells[i];
	}	

	size--;
}


void BTree::TreeNode::removeFromNonLeaf(int index) 
{
	string k = keyCells[index].key;

	if (childrens[index]->size >= T) 
	{
		NodeCell pred = getPredecessor(index);
		keyCells[index] = pred;
		childrens[index]->remove(pred.key);
	}
	else if (childrens[index + 1]->size >= T) 
	{
		NodeCell succ = getSuccessor(index);
		keyCells[index] = succ;
		childrens[index + 1]->remove(succ.key);
	}
	else {
		merge(index);
		childrens[index]->remove(k);
	}
}


BTree::TreeNode::NodeCell BTree::TreeNode::getPredecessor(int index) 
{
	TreeNode* cur = childrens[index];
	while (!cur->isLeaf)
	{
		cur = cur->childrens[cur->size];
	}
		
	return cur->keyCells[cur->size - 1];
}


BTree::TreeNode::NodeCell BTree::TreeNode::getSuccessor(int index)
{
	TreeNode* cur = childrens[index + 1];
	while (!cur->isLeaf)
	{
		cur = cur->childrens[0];
	}

	return cur->keyCells[0];
}


void BTree::TreeNode::fill(int index) 
{
	if (index != 0 && childrens[index - 1]->size >= T)
	{
		borrowFromPrev(index);
	}	
	else if (index != size && childrens[index + 1]->size >= T)
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


void BTree::TreeNode::borrowFromPrev(int index) 
{
	TreeNode* child = childrens[index];
	TreeNode* sibling = childrens[index - 1];

	for (int i = child->size - 1; i >= 0; --i)
	{
		child->keyCells[i + 1] = child->keyCells[i];
	}		

	if (!child->isLeaf) 
	{
		for (int i = child->size; i >= 0; --i)
		{
			child->childrens[i + 1] = child->childrens[i];
		}			
	}

	child->keyCells[0] = keyCells[index - 1];

	if (!child->isLeaf)
	{
		child->childrens[0] = sibling->childrens[sibling->size];
	}

	keyCells[index - 1] = sibling->keyCells[sibling->size - 1];

	child->size++;
	sibling->size--;
}


void BTree::TreeNode::borrowFromNext(int index) 
{
	TreeNode* child = childrens[index];
	TreeNode* sibling = childrens[index + 1];

	child->keyCells[(child->size)] = keyCells[index];

	if (!(child->isLeaf))
	{
		child->childrens[(child->size) + 1] = sibling->childrens[0];
	}

	keyCells[index] = sibling->keyCells[0];

	for (int i = 1; i < sibling->size; ++i)
	{
		sibling->keyCells[i - 1] = sibling->keyCells[i];
	}

	if (!sibling->isLeaf) 
	{
		for (int i = 1; i <= sibling->size; ++i)
		{
			sibling->childrens[i - 1] = sibling->childrens[i];
		}
	}

	child->size++;
	sibling->size--;
}


void BTree::TreeNode::merge(int index) 
{
	TreeNode* child = childrens[index];
	TreeNode* sibling = childrens[index + 1];

	child->keyCells[T - 1] = keyCells[index];

	for (int i = 0; i < sibling->size; ++i)
	{
		child->keyCells[i + T] = sibling->keyCells[i];
	}

	if (!child->isLeaf) 
	{
		for (int i = 0; i <= sibling->size; ++i)
		{
			child->childrens[i + T] = sibling->childrens[i];
		}
	}

	for (int i = index + 1; i < size; ++i)
	{
		keyCells[i - 1] = keyCells[i];
	}

	for (int i = index + 2; i <= size; ++i)
	{
		childrens[i - 1] = childrens[i];
	}

	child->size += sibling->size + 1;
	size--;

	delete(sibling);
}
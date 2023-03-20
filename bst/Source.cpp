#include "BinarySearchTree.h"
#include <iostream>

int main()
{
	BinarySearchTree<int> bst;
	bst.Insert(5);
	bst.Insert(1);
	bst.Insert(4);
	bst.Insert(99);
	std::cout << bst.Search(5);
}
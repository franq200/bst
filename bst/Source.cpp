#include "BinarySearchTree.h"
#include <iostream>

int main()
{
	BinarySearchTree<int> bst;
	bst.Insert(10);
	bst.Insert(9);
	bst.Insert(12);
	bst.Insert(8);
	bst.Insert(7);
	bst.Insert(11);
	bst.PrintAll();
	bst.Remove(10);
	bst.PrintAll();
}
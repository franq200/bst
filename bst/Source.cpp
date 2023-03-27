#include "BinarySearchTree.h"
#include <iostream>

int main()
{
	BinarySearchTree<int> bst;
	bst.Insert(90);
	bst.Insert(80);
	bst.Insert(70);
	bst.Insert(85);
	bst.Insert(65);
	bst.Insert(75);
	bst.Insert(83);
	bst.Insert(87);
	bst.Insert(100);
	bst.Insert(99);
	bst.Insert(110);

	bst.PrintAll();
	bst.Remove(80);
	std::cout << '\n';
	bst.PrintAll();
}
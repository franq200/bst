#include "BinarySearchTree.h"
#include <iostream>
#include "windows.h"
#define _CRTDBG_MAP_ALLOC //to get more details
#include <stdlib.h>  
#include <crtdbg.h>   //for malloc and free

int main()
{
	_CrtMemState sOld;
	_CrtMemState sNew;
	_CrtMemState sDiff;
	_CrtMemCheckpoint(&sOld); //take a snapshot
	{
		BinarySearchTree<int> bst;
		bst.Insert(10);
		bst.Insert(9);
		bst.Insert(8);
		bst.Insert(7);
		bst.Insert(6);
		bst.Insert(5);
		bst.Insert(4);
		bst.Insert(3);
		bst.Insert(2);
		bst.Insert(1);

		bst.PrintAll();
		bst.Balance();
		std::cout << "\n";
		bst.PrintAll();
	}

	_CrtMemCheckpoint(&sNew); //take a snapshot 
	if (_CrtMemDifference(&sDiff, &sOld, &sNew)) // if there is a difference
	{
		OutputDebugString(L"-----------_CrtMemDumpStatistics ---------");
		_CrtMemDumpStatistics(&sDiff);
		OutputDebugString(L"-----------_CrtMemDumpAllObjectsSince ---------");
		_CrtMemDumpAllObjectsSince(&sOld);
		OutputDebugString(L"-----------_CrtDumpMemoryLeaks ---------");
		_CrtDumpMemoryLeaks();
	}
}
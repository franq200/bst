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
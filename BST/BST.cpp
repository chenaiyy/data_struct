// BST.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "bst.h"

int main(void)
{
	BSTree<int,int> Test;
	BinaryTreeNode<int> *NTest[100];
	Test.Insert(2);
	Test.Insert(1);
	Test.Insert(3);

	Test.PutIntoArray(NTest);
	NTest[5]=Test.GetByIndex(1);
	cout<<NTest[5]->data;




	return 0;
}


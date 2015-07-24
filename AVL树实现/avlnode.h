#ifndef AVLNODE_
#define AVLNODE_

#include"phonecard.h"

class AvlNode
{
	friend class AvlTree;
public:
	AvlNode():left(NULL),right(NULL),height(0){}
	AvlNode(Phone& d,AvlNode *l=NULL,AvlNode *r=NULL):data(d),left(l),right(r),height(0){}
private:
	AvlNode *left,*right;
	Phone data;
	int height;
};

#endif
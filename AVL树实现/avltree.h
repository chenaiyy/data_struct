#ifndef AVLTREE_
#define AVLTREE_

#include <stdio.h>
#include <stdlib.h>
#include "avlnode.h"
using namespace std;

#define TRUE 1
#define FALSE 0
int flag = FALSE;

class AvlTree
{
public:
	AvlTree():root(0){}
	void Insert(const Phone& x)
	{
		int taller;
		avl_insert(root,x,taller); 
	}
	void Delete(Phone x)
	{
		int taller;
		avl_del(root,x,taller);
	}
	void Inorder(void(*visit)(AvlNode* u)){ avl_inorder(visit,root);}
private:
	AvlNode *root;
	void left_rotation(AvlNode *&parent);
	void right_rotation(AvlNode *&parent);
	void avl_insert(AvlNode *&parent, Phone x, int &unbalanced);
	void swap(AvlNode *p, AvlNode *q)
	{
        Phone temp = p->data;
        p->data = q->data;
        q->data = temp;
	}
	void avl_del(AvlNode *&parent, Phone x, int &unbalanced);
	void avl_inorder(void(*visit)(AvlNode* u),AvlNode* t);
};

void AvlTree::left_rotation(AvlNode *&parent)
{
	AvlNode *child = parent->left;
	if(child->height == 1) 
	{
		parent->left = child->right;
		child->right = parent;
		parent->height = 0;
		parent = child;
	} 
	else 
	{
		AvlNode *grand_child = child->right;
		parent->left = grand_child->right;
		child->right = grand_child->left;
		grand_child->right = parent;
		grand_child->left= child;
		switch(grand_child->height) 
		{
		case 0:         
			parent->height= child->height = 0;
			break;
		case 1:         
			parent->height = -1;
			child->height = 0;
			break;
		case -1:        
			parent->height = 0;
			child->height= 1; 
		}
		parent = grand_child;
	}
	parent->height = 0;
}


void AvlTree::right_rotation(AvlNode *&parent)
{
	AvlNode *child = parent->right;
	if(child->height == -1) 
	{
		parent->right = child->left;
		child->left = parent;
		parent->height = 0;
		parent = child;
	} 
	else 
	{
		AvlNode *grand_child = child->left;
		parent->right = grand_child->left;
		child->left = grand_child->right;
		grand_child->right = child;
		grand_child->left = parent;
		switch(grand_child->height) 
		{
		case 0:         
			parent->height = child->height = 0;
			break;
		case -1:        
			parent->height = 1;
			child->height = 0;
			break;
		case 1:         
			parent->height = 0;
			child->height = -1;
		}
		parent = grand_child;
	}
	parent->height = 0;
}

void AvlTree::avl_insert(AvlNode *&parent, Phone x, int &unbalanced)
{
	if(parent == NULL) 
	{
		parent = (AvlNode*)malloc(sizeof(AvlNode));
		parent->left = parent->right = NULL;
		parent->data = x;
		parent->height = 0;
		unbalanced = TRUE;
	} 
	else if(x.name < parent->data.name)
	{
		avl_insert(parent->left, x, unbalanced);
		if(unbalanced) 
		{
			switch(parent->height)
			{
			case 0:         
				parent->height = 1;
				break;
			case -1:        
				parent->height = 0;
				unbalanced = FALSE;
				break;
			case 1:         
				left_rotation(parent);
				unbalanced = FALSE;
			}
		}
	} 
	else if(x.name > parent->data.name)
	{
		avl_insert(parent->right, x, unbalanced);
		if(unbalanced) 
		{
			switch(parent->height) 
			{
			case 0:        
				parent->height = -1;
				break;
			case 1:       
				parent->height = 0;
				unbalanced = FALSE;
				break;
			case -1:       
				right_rotation(parent);
				unbalanced = FALSE;
			}
		}
	} 
	else 
		unbalanced = FALSE;
	
}

void AvlTree::avl_del(AvlNode *&parent, Phone x, int &unbalanced)
{
	if(parent->data.name == x.name) 
	{
		unbalanced = TRUE;
		if(!parent->right && !parent->left) 
			parent = NULL;
		else if(parent->right && !parent->left)
			parent = parent->right;
		else if(parent->left && !parent->right)
			parent = parent->left;
		else if(parent->left && parent->right) 
		{
			AvlNode *p = parent;
			p = p->right;
			while(p->left) 
				p = p->left;
			swap(parent, p);
			avl_del(parent->right, x, unbalanced);
		}
	} 
	else if(x.name > parent->data.name) 
	{
		if(!parent->right) 
			return;
		avl_del(parent->right, x, unbalanced);
		if(unbalanced) 
		{
			switch(parent->height)
			{
			case 0:        
				parent->height = 1;
				unbalanced = FALSE;
				break;
			case -1:        
				parent->height = 0;
				unbalanced = FALSE;
				break;
			case 1:         
				left_rotation(parent);
			}
		}
	} 
	else if(x.name < parent->data.name)
	{
		if(!parent->left) 
			return;
		avl_del(parent->left, x, unbalanced);
		if(unbalanced)
		{
			switch(parent->height) 
			{
			case 0:         
				parent->height = -1;
				unbalanced = FALSE;
				break;
			case 1:         
				parent->height = 0;
				unbalanced = FALSE;
				break;
			case -1:              
				right_rotation(parent);
			}
		}
	}
}

void AvlTree::avl_inorder(void(*visit)(AvlNode* u),AvlNode* t)
{
	if(t)
	{
		avl_inorder(visit,t->left);
		visit(t);
		avl_inorder(visit,t->right);
	}
}

void Store(AvlNode* u)
{
	if(u)
		vec.push_back(u);
}

#endif
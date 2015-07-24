#ifndef AVLTREE_
#define AVLTREE_

#include <stdio.h>
#include <stdlib.h>
#include "avlnode.h"
#include "string"
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
	void Insert1(const Phone& x)   //按手机号码插入
	{
		int taller;
		avl_insert1(root,x,taller); 
	}
	void Insert2(const Phone& x) //按办公号码插入
	{
		int taller;
		avl_insert2(root,x,taller); 
	}
	void Insert3(const Phone& x)  //按住宅号码插入
	{
		int taller;
		avl_insert3(root,x,taller); 
	}
	void Delete(AvlNode *x)
	{
		int taller;
		avl_del(root,x->data,taller);
	}
	void Inorder(void(*visit)(AvlNode* u)){ avl_inorder(visit,root);}
	bool Search(AvlNode* &pt,char key[]);
	bool Search1(Phone &pt,char key[]);
	bool Search2(Phone &pt,char key[]);
	bool Search3(Phone &pt,char key[]);
	bool Search4(Phone &pt,char key[]);
private:
	AvlNode *root;
	void left_rotation(AvlNode *&parent);
	void right_rotation(AvlNode *&parent);
	void avl_insert(AvlNode *&parent, Phone x, int &unbalanced);
	void avl_insert1(AvlNode *&parent, Phone x, int &unbalanced);
	void avl_insert2(AvlNode *&parent, Phone x, int &unbalanced);
	void avl_insert3(AvlNode *&parent, Phone x, int &unbalanced);
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
	else if(strcmp(parent->data.name,x.name)>0)
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
	else if(strcmp(parent->data.name,x.name)<0)
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
	if(strcmp(parent->data.name,x.name)==0) 
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
	else if(strcmp(parent->data.name,x.name)<0) 
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
	else if(strcmp(parent->data.name,x.name)>0)
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

bool AvlTree::Search(AvlNode* &pt,char key[])
{
	AvlNode* p=root;
	while(p)
	{
		if(strcmp(p->data.name,key)<0)
			p=p->right;
		else if(strcmp(p->data.name,key)>0)
			p=p->left;
		else
		{
			pt=p;
			return true;
		}
	}
	return false;
}

bool AvlTree::Search1(Phone &pt,char key[])
{
	AvlNode* p=root;
	while(p)
	{
		if(strcmp(p->data.tel_phone,key)<0)
			p=p->right;
		else if(strcmp(p->data.tel_phone,key)>0)
			p=p->left;
		else
		{
			pt=p->data;
			return true;
		}
	}
	return false;
}

bool AvlTree::Search2(Phone &pt,char key[])
{
	AvlNode* p=root;
	while(p)
	{
		if(strcmp(p->data.home_phone,key)<0)
			p=p->right;
		else if(strcmp(p->data.home_phone,key)>0)
			p=p->left;
		else
		{
			pt=p->data;
			return true;
		}
	}
	return false;
}

bool AvlTree::Search3(Phone &pt,char key[])
{
	AvlNode* p=root;
	while(p)
	{
		if(strcmp(p->data.off_phone,key)<0)
			p=p->right;
		else if(strcmp(p->data.off_phone,key)>0)
			p=p->left;
		else
		{
			pt=p->data;
			return true;
		}
	}
	return false;
}

bool AvlTree::Search4(Phone &pt,char key[])
{
	AvlNode* p=root;
	while(p)
	{
		if(strcmp(p->data.name,key)<0)
			p=p->right;
		else if(strcmp(p->data.name,key)>0)
			p=p->left;
		else
		{
			pt=p->data;
			return true;
		}
	}
	return false;
}

void AvlTree::avl_insert1(AvlNode *&parent, Phone x, int &unbalanced)
{
	
	if(parent == NULL) 
	{
		parent = (AvlNode*)malloc(sizeof(AvlNode));
		parent->left = parent->right = NULL;
		parent->data = x;
		parent->height = 0;
		unbalanced = TRUE;
	} 
	else if(strcmp(parent->data.tel_phone,x.tel_phone)>0)
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
	else if(strcmp(parent->data.tel_phone,x.tel_phone)<0)
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

void AvlTree::avl_insert2(AvlNode *&parent, Phone x, int &unbalanced)
{
	
	if(parent == NULL) 
	{
		parent = (AvlNode*)malloc(sizeof(AvlNode));
		parent->left = parent->right = NULL;
		parent->data = x;
		parent->height = 0;
		unbalanced = TRUE;
	} 
	else if(strcmp(parent->data.off_phone,x.off_phone)>0)
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
	else if(strcmp(parent->data.off_phone,x.off_phone)<0)
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

void AvlTree::avl_insert3(AvlNode *&parent, Phone x, int &unbalanced)
{
	
	if(parent == NULL) 
	{
		parent = (AvlNode*)malloc(sizeof(AvlNode));
		parent->left = parent->right = NULL;
		parent->data = x;
		parent->height = 0;
		unbalanced = TRUE;
	} 
	else if(strcmp(parent->data.home_phone,x.home_phone)>0)
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
	else if(strcmp(parent->data.home_phone,x.home_phone)<0)
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

#endif
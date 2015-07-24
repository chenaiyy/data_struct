// bst.h
// unbalanced binary search trees
#ifndef BSTree_
#define BSTree_

#include <vector>
#include "bbinary.h"
#include "xcept.h"
//#include <iostream>
using namespace std;
vector <BinaryTreeNode<int>* > vect;

template<class E, class K>
class BSTree : public BinaryTree<E> {
   public:
	   bool Search(const K& k, E& e) const;
	   BSTree<E,K>& Insert(const E& e);
	   BSTree<E,K>& InsertVisit
		   (const E& e, void(*visit)(E& u));
	   BSTree<E,K>& Delete(const K& k, E& e);
	   void Ascend() {InOutput();}
	   
	   //***************************************作业***********************************************//
	   BinaryTreeNode<E>* TreeMax(BinaryTreeNode<E> *RootNode);  /*以它为根的子树中，关键值最大的一个节点*/
	   BinaryTreeNode<E>* TreeMin(BinaryTreeNode<E> *RootNode);  /*以它为根的子树中，关键值最小的一个节点*/
	   BinaryTreeNode<E>*  TreePrev(BinaryTreeNode<E> *RootNode);/*它在中序遍列中的前一个节点*/
	   BinaryTreeNode<E>*  TreeNext(BinaryTreeNode<E> *RootNode);/*它在中序遍列中的下一个节点*/
	   BinaryTreeNode<E>* GetByIndex(int i);   /*从小到大排序后下标为i的节点，i从0开始*/
	   void PutIntoArray(BinaryTreeNode<E>**);                   /*把树中节点按照关键字由小到大的顺序，放进一个数组ToArray*/
//	   void Store(BinaryTreeNode<E> *u);       /*中序遍 历调用的指针函数*/  
		  //***************************************作业**********************************************//
};

template<class E, class K>
bool BSTree<E,K>::Search(const K& k, E &e) const
{// Search for element that matches k.
   // pointer p starts at the root and moves through
   // the tree looking for an element with key k
   BinaryTreeNode<E> *p = root;
   while (p) // examine p->data
      if (k < p->data) p = p->LeftChild;
      else if (k > p->data) p = p->RightChild;
           else {// found element
                 e = p->data;
                 return true;}
   return false;
}

template<class E, class K>
BSTree<E,K>& BSTree<E,K>::Insert(const E& e)
{// Insert e if not duplicate.
   BinaryTreeNode<E> *p = root,  // search pointer
                     *pp = 0;    // parent of p
   // find place to insert
   while (p) {// examine p->data
      pp = p;
      // move p to a child
      if (e < p->data) p = p->LeftChild;
      else if (e > p->data) p = p->RightChild;
           else throw BadInput(); // duplicate
      }

   // get a node for e and attach to pp
   BinaryTreeNode<E> *r = new BinaryTreeNode<E> (e);
   if (root) {// tree not empty
      if (e < pp->data) pp->LeftChild = r;
      else pp->RightChild = r;}
   else // insertion into empty tree
        root = r;

   return *this;
}

template<class E, class K>
BSTree<E,K>& BSTree<E,K>::InsertVisit
               (const E& e, void(*visit)(E& u))
{// Insert e if not duplicate.
 // Visit e if duplicate.

   // search for a matching element
   BinaryTreeNode<E> *p = root, // search pointer
                     *pp = 0;   // parent of p
   while (p) {// examine p->data
      pp = p;
      if (e < p->data) p = p->LeftChild;
      else if (e > p->data) p = p->RightChild;
           else {// duplicate
                 visit(p->data);
                 return *this;};
      }

   // not a duplicate
   // get a node for e and attach to pp
   BinaryTreeNode<E> *r = new BinaryTreeNode<E> (e);
   if (root) {// tree not empty
      if (e < pp->data) pp->LeftChild = r;
      else pp->RightChild = r;}
   else // insertion into empty tree
        root = r;

   return *this;
}

template<class E, class K>
BSTree<E,K>& BSTree<E,K>::Delete(const K& k, E& e)
{// Delete element with key k and put it in e.

   // set p to point to node with key k
   BinaryTreeNode<E> *p = root, // search pointer
                     *pp = 0;   // parent of p
   while (p && p->data != k){// move to a child of p
      pp = p;
      if (k < p->data) p = p->LeftChild;
      else p = p->RightChild;
      }
   if (!p) throw BadInput(); // no element with key k

   e = p->data;  // save element to delete

   // restructure tree
   // handle case when p has two children
   if (p->LeftChild && p->RightChild) {// two children
      // convert to zero or one child case
      // find largest element in left subtree of p
      BinaryTreeNode<E> *s = p->LeftChild,
                        *ps = p;  // parent of s
      while (s->RightChild) {// move to larger element
         ps = s;
         s = s->RightChild;}

      // move largest from s to p
      p->data = s->data;
      p = s;
      pp = ps;}

   // p has at most one child
   // save child pointer in c
   BinaryTreeNode<E> *c;
   if (p->LeftChild) c = p->LeftChild;
   else c = p->RightChild;

   // delete p
   if (p == root) root = c;
   else {// is p left or right child of pp?
         if (p == pp->LeftChild)
              pp->LeftChild = c;
         else pp->RightChild = c;}
   delete p;

   return *this;
}

//*******************************************************作业***********************************************//
template<class E, class K>
BinaryTreeNode<E>* BSTree<E,K>::TreeMax(BinaryTreeNode<E> *RootNode)/*找以RootNode为根节点树的右子树...*/
{
	if(!RootNode)
		throw BadInput();
	while (RootNode->RightChild)    /*循环遍历找到其最下端右叶子节点*/
		RootNode=RootNode->RightChild;
	return RootNode;
}

template<class E, class K>
BinaryTreeNode<E>* BSTree<E,K>::TreeMin(BinaryTreeNode<E> *RootNode)
{
	if(!RootNode)
		throw BadInput();
	while(RootNode->LeftChild)  /*循环遍历找到其最下端左叶子节点*/
		RootNode=RootNode->LeftChild;
	return RootNode;
};

/*template<class E, class K>
BinaryTreeNode<E>*  BSTree<E,K>::TreePrev(BinaryTreeNode<E> *RootNode)// 行不通//
{
	   BinaryTreeNode<E> *p = root, *pp = 0; 
	   while (p&&p->data!=RootNode->data)
	   {
		   pp=p;
		   if (p->data>RootNode->data)                                      
			   p=p->LeftChild;
		   else
			   p=p->RightChild;
	   }
	   if(p)
	   {
		   if(p->LeftChild)
			   return p->LeftChild;
		   else
			   return pp;
	   }
	   return NULL;
}BinaryTreeNode<int>* */





/*template<class E, class K>
void BSTree<E,K>::Store(BinaryTreeNode<E> *u)  
{

	vect.pop_back(u);
	
}*/

void Store(BinaryTreeNode<int> *u){vect.push_back(u);}

template<class E, class K>
BinaryTreeNode<E>*  BSTree<E,K>::TreePrev(BinaryTreeNode<E> *RootNode)  /*对树进行中序遍历存储在容器中后*/
{
	InOrder(Store);                                                     /*在容器中找到其前一个节点*/
	if(vect[0]==RootNode)  //没有前一个节点，返回空
		return NULL;
	for(vector<BinaryTreeNode<E>* >::iterator itr=vect.begin();*itr!=RootNode;itr++);
	return *(--itr);
}

template<class E, class K>
BinaryTreeNode<E>*  BSTree<E,K>::TreeNext(BinaryTreeNode<E> *RootNode)  /*对树进行中序遍历存储在容器中后*/
{
	InOrder(Store);                                                      /*在容器中找到其后一个节点*/
	if(vect[vect.size()-1]==RootNode)  //没有后一个节点，返回空
		return NULL;
	for(vector<BinaryTreeNode<E>* >::iterator itr=vect.begin();*itr!=RootNode;itr++);
	return *(++itr);

}


template<class E, class K>
BinaryTreeNode<E>*  BSTree<E,K>:: GetByIndex(int i)
{
	InOrder(Store);   //BST树的特性，中序遍历后其关键值恰好从小到大排列
	return vect[i];
}

template<class E, class K>
void BSTree<E,K>::PutIntoArray(BinaryTreeNode<E>* ToArray[])
{
	 
	InOrder(Store);
	for(int i=0;i<vect.size();i++)
	{
		ToArray[i]=vect[i];
		cout<<(*vect[i]).data<<" ";
	}
}


//*******************************************************作业*************************************************//

#endif

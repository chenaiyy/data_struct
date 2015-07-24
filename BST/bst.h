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
	   
	   //***************************************��ҵ***********************************************//
	   BinaryTreeNode<E>* TreeMax(BinaryTreeNode<E> *RootNode);  /*����Ϊ���������У��ؼ�ֵ����һ���ڵ�*/
	   BinaryTreeNode<E>* TreeMin(BinaryTreeNode<E> *RootNode);  /*����Ϊ���������У��ؼ�ֵ��С��һ���ڵ�*/
	   BinaryTreeNode<E>*  TreePrev(BinaryTreeNode<E> *RootNode);/*������������е�ǰһ���ڵ�*/
	   BinaryTreeNode<E>*  TreeNext(BinaryTreeNode<E> *RootNode);/*������������е���һ���ڵ�*/
	   BinaryTreeNode<E>* GetByIndex(int i);   /*��С����������±�Ϊi�Ľڵ㣬i��0��ʼ*/
	   void PutIntoArray(BinaryTreeNode<E>**);                   /*�����нڵ㰴�չؼ�����С�����˳�򣬷Ž�һ������ToArray*/
//	   void Store(BinaryTreeNode<E> *u);       /*����� �����õ�ָ�뺯��*/  
		  //***************************************��ҵ**********************************************//
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

//*******************************************************��ҵ***********************************************//
template<class E, class K>
BinaryTreeNode<E>* BSTree<E,K>::TreeMax(BinaryTreeNode<E> *RootNode)/*����RootNodeΪ���ڵ�����������...*/
{
	if(!RootNode)
		throw BadInput();
	while (RootNode->RightChild)    /*ѭ�������ҵ������¶���Ҷ�ӽڵ�*/
		RootNode=RootNode->RightChild;
	return RootNode;
}

template<class E, class K>
BinaryTreeNode<E>* BSTree<E,K>::TreeMin(BinaryTreeNode<E> *RootNode)
{
	if(!RootNode)
		throw BadInput();
	while(RootNode->LeftChild)  /*ѭ�������ҵ������¶���Ҷ�ӽڵ�*/
		RootNode=RootNode->LeftChild;
	return RootNode;
};

/*template<class E, class K>
BinaryTreeNode<E>*  BSTree<E,K>::TreePrev(BinaryTreeNode<E> *RootNode)// �в�ͨ//
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
BinaryTreeNode<E>*  BSTree<E,K>::TreePrev(BinaryTreeNode<E> *RootNode)  /*����������������洢�������к�*/
{
	InOrder(Store);                                                     /*���������ҵ���ǰһ���ڵ�*/
	if(vect[0]==RootNode)  //û��ǰһ���ڵ㣬���ؿ�
		return NULL;
	for(vector<BinaryTreeNode<E>* >::iterator itr=vect.begin();*itr!=RootNode;itr++);
	return *(--itr);
}

template<class E, class K>
BinaryTreeNode<E>*  BSTree<E,K>::TreeNext(BinaryTreeNode<E> *RootNode)  /*����������������洢�������к�*/
{
	InOrder(Store);                                                      /*���������ҵ����һ���ڵ�*/
	if(vect[vect.size()-1]==RootNode)  //û�к�һ���ڵ㣬���ؿ�
		return NULL;
	for(vector<BinaryTreeNode<E>* >::iterator itr=vect.begin();*itr!=RootNode;itr++);
	return *(++itr);

}


template<class E, class K>
BinaryTreeNode<E>*  BSTree<E,K>:: GetByIndex(int i)
{
	InOrder(Store);   //BST�������ԣ������������ؼ�ֵǡ�ô�С��������
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


//*******************************************************��ҵ*************************************************//

#endif

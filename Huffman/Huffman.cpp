// Huffman.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "binary.h"
#include "minheap.h"
#include <string>
#include <vector>
#include "huffman.h"
#include <iostream>
using namespace std;

template <class T>
BinaryTree<int> HuffmanTree(T a[], int n)
{// Generate Huffman tree with weights a[1:n].
	// create an array of single node trees
	Huffman<T> *w = new Huffman<T> [n+1];
	BinaryTree<int> z, zero;
	for (int i = 1; i <= n; i++) {
		z.MakeTree(i, zero, zero);
		w[i].weight = a[i-1];
		w[i].tree = z;
	}
	
	// make array into a min heap
	MinHeap<Huffman<T> > H(1);
	H.Initialize(w,n,n);
	
	// repeatedly combine trees from heap
	Huffman<T> x, y;
	for (i = 1; i < n; i++) {
		H.DeleteMin(x);
		H.DeleteMin(y);
		z.MakeTree(0, x.tree, y.tree);
		x.weight += y.weight; x.tree = z;
		H.Insert(x);
	}
	
	H.DeleteMin(x); // final tree
	H.Deactivate();
	delete [] w;
	return x.tree;
}

string InPut()    //字符串的输入
{
	string str;
	std::cout<<"输入一个字符一个字符串：";
	std::cin>>str;
	std::cout<<"输入的字符串为："<<str<<endl;

	return str;
}

#include <vector>
void Statistic(string &str1,vector<char>&str2,vector<int> &a,int &num)    //字符串的统计
{
	int n=1;
	for( int i=str1.size()-1;i>1;i--)
		for(int j=0;j<i;j++)
		{
			if(str1[j]>str1[j+1])
				swap(str1[j],str1[j+1]);
		}
//		std::cout<<str1<<endl;
		char ch=str1[0];
		str2.push_back(ch);
	for( i=1;i<str1.size();i++)
	{
		if(ch!=str1[i])
		{
			num++;
			ch=str1[i];
			str2.push_back(ch);
			a.push_back(n);
			n=1;
		}
		else
			n++;
	}
	a.push_back(n);
}

vector<string> vec1;       //存储编码，为最后得到WPL做准备
void visit(BinaryTreeNode<int> *tem,string str)//Huffman编码
{
	if (tem->LeftChild)
	{
		str=str+'0';
		visit(tem->LeftChild,str);
		str.erase(str.length()-1);
	}
	
	if(tem->RightChild)
	{
		str=str+'1';
		visit(tem->RightChild,str);
		str.erase(str.length()-1);
	}
	if(tem->LeftChild==0&&tem->RightChild==0)
		vec1.push_back(str);
/*	{
		for (int i=0;i<str.length();i++)
			std::cout<<str[i];
		std::cout<<" ";

	}*/
}

vector<int> vec;  //存储前序遍历得到带编码字符的序号，以便编码与字符相对应
void Store(BinaryTreeNode<int>* u)
{
		  if(u->data!=0)
			  vec.push_back(u->data);
}

int main(int argc, char* argv[])
{
	int num=1,WPL=0;
	string str1,mystr;
	vector<char> str2;
	vector<int> order;
	vector<int> n;
	str1=InPut();
	Statistic(str1,str2,n,num);    //统计字符的字符串

	std::cout<<"出现的字符：";
	for( int i=0;i<str2.size();i++)
		std::cout<<str2[i]<<" ";
	std::cout<<endl;

	int* a=new int[num];
	for(i=0;i<num;i++)
		a[i]=n[i];
	std::cout<<"出现的次数：";
	for(i=0;i<num;i++)
		std::cout<<a[i]<<" ";
	std::cout<<endl;

	BinaryTree<int>Tree=HuffmanTree(a,num);
	Tree.PostOrder(Store);
	visit(Tree.root,mystr);

	std::cout<<"字符及其相关编码："<<endl;
	for(i=0;i<vec.size();i++)
		std::cout<<str2[vec[i]-1]<<' '<<vec1[i]<<endl;

	for(i=0;i<vec.size();i++)
		WPL+=a[vec[i]-1]* vec1[i].size();

	std::cout<<"WPL是："<<WPL<<endl;

	system("pause");
	
	return 0;
}


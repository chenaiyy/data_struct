#ifndef LiearList_
#define LiearList_


#include <iostream>
using namespace std;

class LiearList
{
public:
	LiearList();
	~LiearList(){delete[]element;}
	int Length()const{return length;}
	LiearList& Insert(int k,const int& x)
	{
		if (k<0||k>length)
			cout<<"不存在第"<<k<<"个元素！"<<endl;
		if(length==MaxSize)
			Resize(2*MaxSize);
		if(length<MaxSize/4)
			Resize(MaxSize/2);
		
		for (int i=length-1;i>=k;i--)
			element[i+1]=element[i];
		element[k]=x;
		length++;
		return *this;
		
	}
	int& operator[](int i);
	void Resize(int size);
private:
	int length;
	int MaxSize;
	int *element;
};

LiearList::LiearList()
{
	MaxSize=1;
	element=new int[MaxSize];
	length=0;
}


void LiearList::Resize(int size)
{
    int sz=length;
	int *newelement=new int[size];
	
	int *srcptr=element;
	int *desptr=newelement;
	
	
	while(length--)
		
		*desptr++=*srcptr++;
	
	delete []element;
	element=newelement;
	MaxSize=size;
	length=sz;
	
}

int& LiearList::operator [](int i)
{
	if (i<0||i>length-1)
		cerr<<"error!";
    else
		return element[i];
}

#endif
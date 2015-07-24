#ifndef _STRUCT_H
#define _STRUCT_H

struct node
{
	node (BYTE a2=0,UINT a3=0,int a1=0,node *a4=NULL,node *a5=NULL)
	{
	  psize=a2;
	  dsize=a3;
	  length=a1;
	  next=a4;
	  pre=a5;
	}

	int length;   //段长
	BYTE psize;     //像素位数
	UINT dsize;    //第几段
	node *next;
	node *pre;
};
#endif
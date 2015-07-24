#include "stdafx.h"
#include "operate.h"
#include "struct.h"
#include <bitset>
#include <iostream>
using namespace std;


bool compress::comp(CString filename,CProgressCtrl *pro1)
{
	BITMAPFILEHEADER	FileHeader;				// 位图头文件
	BITMAPINFOHEADER	InfoHeader;
    int				ImageSize;
	BYTE*	 m_data;			// 图像字节数据
	int		m_bpp;			// 图像灰度值
	int		m_width;		// 图像宽度
	int		m_height;		// 图像深度
	
	int count=0;               //记录是第几段
	int m=0;                 //记录像位
	int n=0;                //记录段数
	int len;
	int b2=0;
	ULONGLONG i_2=0;            //记录图片文件大小
	unsigned short i_3;         //记录像素矩阵后的信息大小
	BYTE *garry;                //记录像素矩阵后的信息

	CFile bfile;
	CFile endfile;
	CString efilename=filename+".zj";
	if(bfile.Open(filename,CFile::modeReadWrite ,NULL))
	{
		bfile.Read(&FileHeader, sizeof(BITMAPFILEHEADER));
		if (FileHeader.bfType != 0x4D42)								// 检查一般位图id
		{
			MessageBox(NULL, _T("Could not match BMP type"), _T("ERROR"), MB_OK);
			bfile.Close();		
			return false;
		}

		bfile.Read(&InfoHeader, sizeof(BITMAPINFOHEADER));
		b2=FileHeader.bfOffBits;
		bfile.Seek(FileHeader.bfOffBits,CFile::begin);
	}
	m_width	  = InfoHeader.biWidth;
	m_height  = InfoHeader.biHeight;
	m_bpp	  = InfoHeader.biBitCount;
	ImageSize = m_width * m_height*InfoHeader.biBitCount/8;
	m_data	  = new BYTE [ImageSize];						// 定位位图数据
	if (m_data==NULL)												
	{
		MessageBox(NULL, _T("Could not allocate memory for image"), _T("SHUTDOWN ERROR"),MB_OK | MB_ICONINFORMATION);
		bfile.Close();
		return false;
	}

	bfile.Read(m_data,ImageSize);
	i_2=bfile.GetLength();
	i_3=unsigned short(i_2-(ImageSize+b2));
	if(i_3>0)
	{
		garry=new BYTE[i_3];
		bfile.Read(garry,i_3);
	}

	if (m_data==NULL)												// 确保位图被读取
	{
		MessageBox(NULL, _T("Could not read image data"), _T("SHUTDOWN ERROR"),MB_OK | MB_ICONINFORMATION);
		bfile.Close();
		return false;
	}
	bfile.SeekToBegin();
	BYTE *earry=new BYTE[b2];
	bfile.Read(earry,b2);
	bfile.Close();
    node *head=NULL;
	node *p1,*p2;
	for(int i=0;i<ImageSize;i++)
	{
		m=getsize(m_data[i]);
		if(head==NULL)
		{
			n++;
			head = new node(m,++count,n);
			p1 = head;
			continue;
		}
		if(p1->psize==m)
		{
			if(n<256)
			{
			n++;
			p1->length=n;
			}
			else
			{
				n=1;
				p2=new node(m,++count,n,NULL,p1);
				p1->next=p2;
			    p1 = p2;
			}

		}
		else
		{
			n=1;
			p2 =new node(m,++count,n,NULL,p1);
			p1->next=p2;
			p1 = p2;
		}
	}
	node *last=p2;
    
	int *larry=new int[count+1];
	BYTE *barry=new  BYTE[count+1];
	int *sarry=new int[count+1];
	int *kay=new int[count+1];

	for(node *p3=head;p3;p3=p3->next)
	{
		larry[p3->dsize]=p3->length;
		barry[p3->dsize]=p3->psize;
	}

	Vbits(larry,barry,count,sarry,kay);

	node *p4=last;
	node *p5,*p6;
	int len1 = 0;
    int len2 = 0;
	unsigned short len3=0;//合并后的段长
	BYTE pmax=0;//记录像位最大长度 
	for(int i=count;i>0;i--)
	{
		len2=kay[i];
		len=len2-1;
		while(len)
		{
			len1+=p4->length;
			if(pmax<p4->psize)
				pmax=p4->psize;
			p6=p4;
			p4=p4->pre;
		    delete p6;
			len--;
		}
		len1+=p4->length;
		if(pmax<p4->psize)
				pmax=p4->psize;
		p4->length=len1;
		p4->psize=pmax;
		len1=0;
		pmax=0;
		if(i==count)
		{
			p4->next=NULL;
			last=p4;
		}
		else
		{
			p4->next=p5;
		}	
		p5=p4;
		p4=p4->pre;
		len3++;
		if(p4==NULL)
			break;
		i=i-len2+1;
	}

	delete []larry;
	delete []barry;
	delete []sarry;
	delete []kay;

    BYTE *larry1=new BYTE[len3+1];
	BYTE *barry1=new  BYTE[len3+1];

    int i_1=1;
	for(node *p3=head;p3;p3=p3->next,i_1++)
	{
		p3->dsize=i_1;
		larry1[i_1]=p3->length-1;
		barry1[i_1]=p3->psize;
	}
    
    ///////////////////////////////////////////////////////////////////////////////////////
	unsigned short len4 = 3*len3/32+1;
	UINT *uarry= new UINT[len4];
	CString str_1,str_2;
	unsigned short m_1=0;
	unsigned short m_3=0;
	short y3=0;
	for(int i=1;i<=len3;i++)
	{
		str_1 = btoa((barry1[i]-1),3);
		m_1=str_2.GetLength();
		if((m_1+3)<32)
		{
			str_2.Append(str_1);
			m_1 = m_1+3;
		}
		else
		{
			int m_2=32-m_1;
			for(int p=0;p<m_2;p++)
				str_2.AppendChar(str_1[p]);
			uarry[m_3++] = atou(str_2);
			str_2="\0";
			for(int p=m_2;p<3;p++)
				str_2.AppendChar(str_1[p]);
			m_1=str_2.GetLength();
		}
	}
	if(m_1!=32)
	{
		y3=32-m_1;
		for(int i=y3;i>0;i--)
			str_2.AppendChar('0');
		uarry[m_3]=atou(str_2);
	}
	
	///////////////////////////////////////////////////////////////////////////////////////
    int m1,m2,m3;
	m3=0;
	UINT value =0;
	UINT v_count=0;
	CString str,str1;
	
	if((endfile.Open(efilename,CFile::modeReadWrite|CFile::modeCreate,NULL)))
	{
		endfile.Seek(b2+12,CFile::begin);
		endfile.Write(&len3,2);
		endfile.Write(larry1,len3+1);
		endfile.Write(uarry,len4*4);
		int j;
		int i;
		int k=len3;
		//int k=int(length/1024);
		if(!k)
			k=1;
		int r_k=10000/k;
		pro1->SetRange32(0,10000);
		pro1->SetPos(0);
		int pos = 0;
		int kb = 0;
		for(p1=head;p1;p1=p1->next)
		{
			pos =(kb++)*r_k;
			pro1->SetPos(pos);
			len=p1->length;
			i=0;
			
			for(j=0;j<len;j++)
			{
				i=j+m3;
				str1=btoa(m_data[i],p1->psize);
				m1=str1.GetLength();
				m2=str.GetLength();
				if((m1+m2)<32)
				{
					str+=str1;
					m2=m2+m1;
				}
				else
				{
					int k=32-m2;
					for(int p=0;p<k;p++)
						str.AppendChar(str1[p]);
					value = atou(str);
					endfile.Write(&value,4);
					++v_count;
					value=0;
					str="\0";
					for(int p=k;p<m1;p++)
						str.AppendChar(str1[p]);
					m2=str.GetLength();
				}
			}
			m3+=len;
		}
		if(m2!=32)
		{
			int y1=32-m2;
			for(int i=y1;i>0;i--)
				str.AppendChar('0');
			value=atou(str);
			endfile.Write(&value,4);
			++v_count;
			if(i_3>0)
			{
				endfile.Write(garry,i_3);
				delete []garry;
			}
			short y2=m2;
			pro1->SetPos(10000);

			endfile.SeekToBegin();
			endfile.Write(earry,b2);
			endfile.Write(&m_1,2);
			endfile.Write(&len4,2);
			endfile.Write(&y2,2);
			endfile.Write(&v_count,4);
			endfile.Write(&i_3,2);

		}
		endfile.Close();
	}
	else 
		return false;
    delete []earry; 
	delete []larry1;
	delete []barry1;
	delete []m_data;
	delete []uarry;
	
	node *tempnode;
	while(head)
	{
		tempnode = head->next;
		delete head;
		head=tempnode;
	}

    return true;
}
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool compress::uncomp(CString bfilename, CString efilename,CProgressCtrl *pro1)
{
	CFile file1;
	CFile file2;
	short e1;
	int b2=0;
	unsigned short e2,e5,e6;
	UINT e3;
	unsigned short e4=0;
	BYTE value;
	BITMAPFILEHEADER fileheader;
	BYTE *garry1;

	if((file1.Open(efilename,CFile::modeReadWrite|CFile::modeCreate,NULL))&&(file2.Open(bfilename,CFile::modeReadWrite ,NULL)))
	{
		file2.Read(&fileheader,sizeof(BITMAPFILEHEADER));
		b2=fileheader.bfOffBits;
		BYTE *earry1=new BYTE[b2];
		file2.SeekToBegin();
		file2.Read(earry1,b2);
		file1.Write(earry1,b2);                             
		file2.Read(&e5,2);
		file2.Read(&e6,2);
		file2.Read(&e1,2);
		file2.Read(&e3,4);
		file2.Read(&e4,2);
		file2.Read(&e2,2);
		BYTE* larry=new BYTE[e2+1];
		BYTE* barry=new BYTE[e2+1];
		UINT* uarry=new UINT[e6];                                        
		file2.Read(larry,e2+1);
		file2.Read(uarry,e6*4);
		UINT *darry=new UINT[e3];

		file1.Seek(b2,CFile::begin);
		file2.Read(darry,e3*4);
		if(e4>0)
		{
			garry1=new BYTE[e4];
			file2.Read(garry1,e4);
		}

		CString str_1,str_2;
		int w1=1;//计数
		int w2=0;
        for(int i=0;i<e6;i++)
		{
			if(i==(e6-1))
			{
				uarry[i]=uarry[i]>>(32-e5);
				str_1 +=utoa(uarry[i],e5-1);
				w2=str_1.GetLength();

			}
			else
			{
				str_1+=utoa(uarry[i],31);
                w2=str_1.GetLength();
			}
			while(w2>2)
			{
				str_2=str_1.Left(3);
				barry[w1++]=atob(str_2)+1;
				w2=w2-3;
				str_1=str_1.Right(w2);
			}
		}

		int k=1;
		int k1=0;
		CString str,str2;
		int count = 0;
		BYTE tarry[1024];
		int km=e3;
		//int k=int(length/1024);
		if(!km)
			km=1;
		int r_k=10000000/km;
		pro1->SetRange32(0,10000000);
		pro1->SetPos(0);
		int pos = 0;
		int kb = 0;

		for(UINT i=0;i<e3;i++)
		{
			pos =(kb++)*r_k;
			pro1->SetPos(pos);
			if(i==(e3-1))
			{
				darry[i]=darry[i]>>(32-e1);
				str +=utoa(darry[i],e1-1);
			}
			else
			{
				str += utoa(darry[i],31);
			}
			int temp=str.GetLength();
			int j;

			for(j=k1;(j<larry[k]+1)&&(temp>=barry[k]);j++)
			{
				str2= str.Left(barry[k]);
				value= atob(str2);
				tarry[count++]=value;
				if(count==1024)
				{
					file1.Write(tarry,1024);
					count=0;
				}
				str=str.Right(str.GetLength()-barry[k]);
				temp=str.GetLength();

			}
			k1=j;
			if(j==larry[k]+1)
			{
				k++;
				k1=0;
			}
		}

		file1.Write(tarry,count);
		if(e4>0)
		{
			file1.Write(garry1,e4);
			delete []garry1;
		}
		pro1->SetPos(10000);
		file1.Close();
		file2.Close();
		delete []larry;
		delete []barry;
		delete []uarry;
		delete []darry;
		delete []earry1;
	}
	else
		return false;
	return true;
}

short compress::getsize(BYTE a)
{
	short temp=0;
	BYTE ch=a;
	do
	{
		ch=ch/2;
		temp++;
	}
	while(ch);
	return temp;
}

void compress::Vbits(int l[], BYTE b[], int n, int s[], int kay[])
{
	int L=256,header=11;
	s[0]=0;
	for(int i=1;i<=n;i++)
	{
		int lsum=l[i];
		int bmax=b[i];
		s[i]=s[i-1]+lsum*bmax;
		kay[i]=1;

		for(int k=2;k<=i&&lsum+l[i-k+1]<=L;k++)
		{
			lsum+=l[i-k+1];
			if(bmax<b[i-k+1])bmax=b[i-k+1];
			if(s[i]>s[i-k]+lsum*bmax)
			{
				s[i]=s[i-k]+lsum*bmax;
				kay[i] = k;
			}
		}
		s[i]+=header;
	}
}

UINT compress::atou(CString  str)
{
	UINT z=0;
	for(int i=0;i<32;i++)
		if(str[i]=='1')
			z+=1<<(31-i);
	return z;
}

CString compress::btoa(BYTE a,BYTE ps)
{
	CString str_1;
    int i=a;
	char y[9];
	itoa(i,y,2);
	str_1.Append(y);
	int j=str_1.GetLength();
	if(j!=ps)
	{
		str_1="\0";
		for(int k=0;k<(ps-j);k++)
			str_1.AppendChar('0');
		str_1.Append(y);
	}
	return str_1;
}

BYTE compress::atob(CString str)
{
	BYTE i=0;
	int u=str.GetLength();
	for(int z=0;z<u;z++)
		if(str[z]=='1')
			i+=1<<(u-z-1);
	return i;
}

CString compress::utoa(UINT c,int m1)
{
	CString str;
	int j=0;
	int str_num;
	char a[32];
	j = c>>1;
	itoa(j,a,2);
	str.Append(a);
	str_num=str.GetLength();
	if(str_num!=m1)
	{
		str="\0";
		for(int l=0;l<(m1-str_num);l++)
			str.AppendChar('0');
		str.Append(a);
	}
	j= c-2*j;
	if(j==1)
		str.AppendChar('1');
	else
		str.AppendChar('0');
	return str;
		
}
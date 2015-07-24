#ifndef Calculater_
#define Calculater_

#include "LiearList.h"
#include <iostream>
using namespace std;

class Calculater
{
public:
	void Input();
	void Computer();
	void Output();
	~Calculater(){}
private:
	int m_oprator;
	LiearList m_Answer;
	
};

void Calculater::Input()
{
	int n;
	cout<<"����Ҫ���ڽ׳˵�����";
	cin>>n;
	
	m_oprator=n;
}

void Calculater::Computer()
{
	int i,sum=1;
	int count=1;

	for (i=1;i<m_oprator+1&&sum<1000*1000*100;i++)   /*��һ��int���ܴ�������׳ˣ��Խ�Լʱ�俪��*/
	{
		sum*=i;
		count++;
	}

	for (i=0;sum>0;i++)
	{
		m_Answer.Insert(i,sum%1000);
		sum/=1000;
	}
	
	int k;
	while (count!=m_oprator+1)                     //��֮��Ľ׳�
	{	
		 k=0;
		for ( i=0;i<m_Answer.Length();i++)  //��̬������ÿ����Ԫ����count
			m_Answer[i]*=count;
		
		for ( i=0;i<m_Answer.Length()-1;i++) //���·��䶯̬�����ÿ����Ԫ��ʹ��ÿ����Ԫֻ�洢��λ
		{
			m_Answer[i]+=k;
			k=0;
			if (m_Answer[i]>999)
			{
				k=m_Answer[i]/1000;
				m_Answer[i]%=1000;
			}
		}
		m_Answer[m_Answer.Length()-1]+=k;
		if (m_Answer[m_Answer.Length()-1]>999)  //���һλ�Ĵ���
		{
			k=m_Answer[m_Answer.Length()-1]/1000;
			m_Answer[m_Answer.Length()-1]%=1000;
			m_Answer.Insert(m_Answer.Length(),k);
		}
		count++;
	}
}

void Calculater::Output()
{
	cout<<m_oprator<<"�Ľ׳˵Ľ���ǣ�";
	for (int i=m_Answer.Length()-1;i>=0;i--)  //����������������λ�Ĳ���
	{
		if(m_Answer[i]>99)
			cout<<m_Answer[i];
		else if(m_Answer[i]>9&&m_Answer[i]<100)
			cout<<0<<m_Answer[i];
		else 
			cout<<0<<0<<m_Answer[i];
	}
	cout<<endl;

}

#endif
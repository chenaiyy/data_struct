#ifndef Calculator_
#define Calculator_

#include<string>
#include "stack.h"
#include "xcept.h"
#include <iostream>
using namespace std;

class Calculator
{
public:
	void Input();
	void DoOperator();
	void OutResult();
private:
	char Judge(char top_ch,char current_ch);
	void PushToStack(double m_figure1,double m_figure2,char ch,Stack<double>&FigureStack);
	
	char m_expression[255];
	int m_count;
	double m_result;
};

void Calculator::Input()   //���ʽ������
{
	int i;
	string str1;
	cout<<"��������Ҫ����ı��ʽ��";
	cin>>str1;
	int m=str1.size();

	if (str1[m-1]=='+'||str1[m-1]=='-'||str1[m-1]=='*'||str1[m-1]=='/')
		throw BadInput();

	for(i=0;i<str1.size();i++)
		m_expression[i]=str1[i];
	m_expression[i]='#';    //���ʽβ����ӡ�#�����Ա�������ֵ
	m_count=i;
}

char Calculator::Judge(char top_ch,char current_ch)   //ջ����������ջ������������ȼ��Ƚ�
{
	char result='<' ;				//Ĭ��С��
	switch(current_ch)
	{
	case'+':case'-':if(top_ch=='('||top_ch=='#')
				result='>' ;
		break ;
	case'*':case'/':if(top_ch=='+'||top_ch=='-'||top_ch=='('||top_ch=='#')
				result='>' ;
		break ;
	case'(':if(top_ch!=')')
				result='>' ;
		break;
	case')':if(top_ch=='(')
				result='=' ;
		break ;
	case'#':if(top_ch=='#')
				result='=' ;
		break ;
	default: result='c';
		break;
	}
	return result ;
}

void Calculator::PushToStack(double m_figure1,double m_figure2,char ch,Stack<double>&FigureStack) //���ʽ�ļ���
{
	double result=0 ;
	switch(ch)
	{
	case'+':result= m_figure1+m_figure2;break ;
	case'-':result= m_figure1-m_figure2;break;
    case'*':result= m_figure1*m_figure2;break;
    case'/':result= m_figure1/m_figure2;break;
    default:break ;
	}
	FigureStack.Add(result);
}

void Calculator::DoOperator()
{
	Stack<double> FigureStack;    //�洢���ʽ�еĲ�����
	Stack<char> CharStack;        //�洢���ʽ�еĲ�����
	CharStack.Add('#');
	static double DotOffset=1;    //С�����ƫ����
	static double Realnumber=0;   //���ʽ�Ĳ�����
	bool Dot=false;                //�Ƿ�һ����ΪС��
	bool NegtiveNumber=false;     //�Ƿ�һ����Ϊ����
	bool IfNumber=false;          //�Ƿ����һ����������
	
	int r=0,l=0;                    //����������
	for (int j=0;j<=m_count;j++)
	{
		if(m_expression[j]=='(')
			l++;
		else if(m_expression[j]==')')
			r++;
	}
	
	if(r!=l)
		throw BadInput();    //���Ų�ƥ�䵼�±��ʽ����
	
	int i=0;
	
	if(m_expression[0]=='-')       //�����-���ڱ��ʽ�ĵ�һλ����Ǹ��ŵı�־
	{
		NegtiveNumber=true;
		i++;
	}
	for (i;i<=m_count;i++)         //�������ʽ
	{
		if ((i>=1&&m_expression[i-1]=='(')&&m_expression[i]=='-')  //�����ĵڶ�����־���ڡ������ı�Ϊ����
		{
			NegtiveNumber=true;
			continue;
		}
		
		if ((m_expression[i]>='0'&&m_expression[i]<='9')||m_expression[i]=='.')        //�����������
		{
			if(m_expression[i]=='.')
				Dot=true;
			else
			{
				IfNumber=true;
				double temp=m_expression[i]-'0';                       //�ַ�ת������
				if(Dot)                                                //С���Ĵ������
				{
					DotOffset/=10;
					Realnumber+=temp*DotOffset;       
				}
				else                                                     //�����Ĵ������
					Realnumber=Realnumber*10+temp;
				
			}
		}
		else
		{
			if(IfNumber)                                          //�Ѳ�����ѹ��ջ��
			{
				if(NegtiveNumber)
					Realnumber=-Realnumber;
				FigureStack.Add(Realnumber);
				Dot=false;                                           //��������
				DotOffset=1;
				Realnumber=0;
				IfNumber=false;
				NegtiveNumber=false;
			}
			                                               //���ַ��Ĵ���
			
				char temp1;
Mark:				CharStack.Delete(temp1);
						char GetResult=Judge(temp1,m_expression[i]);  //��ֵ������
					
					switch(GetResult)
					{
					case '<':
						double NO1,NO2;
						if(FigureStack.IsEmpty())      //���ʽ����
							throw NoMem();
						FigureStack.Delete(NO2);
						if(FigureStack.IsEmpty())      //���ʽ����
							throw NoMem();
						FigureStack.Delete(NO1);
						PushToStack(NO1,NO2,temp1,FigureStack);
						goto Mark;                                   //Ŀǰ�ַ�������һ�εıȽ�
						break;
					case '=':
						break;
					case '>':
						CharStack.Add(temp1);
						CharStack.Add(m_expression[i]);
						break;
					default:
						break;
					}
			
		}
		
	}
	FigureStack.Delete(m_result);                                   //�õ������
}

void Calculator::OutResult()                                           //��������
{
	cout<<"���ʽ����ǣ�"<<m_result;
	cout<<endl;
}

#endif
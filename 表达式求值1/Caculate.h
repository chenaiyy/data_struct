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

void Calculator::Input()   //表达式的输入
{
	int i;
	string str1;
	cout<<"输入你所要计算的表达式：";
	cin>>str1;
	int m=str1.size();

	if (str1[m-1]=='+'||str1[m-1]=='-'||str1[m-1]=='*'||str1[m-1]=='/')
		throw BadInput();

	for(i=0;i<str1.size();i++)
		m_expression[i]=str1[i];
	m_expression[i]='#';    //表达式尾部添加”#“，以便后面的求值
	m_count=i;
}

char Calculator::Judge(char top_ch,char current_ch)   //栈顶操作符与栈外操作符的优先级比较
{
	char result='<' ;				//默认小于
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

void Calculator::PushToStack(double m_figure1,double m_figure2,char ch,Stack<double>&FigureStack) //表达式的计算
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
	Stack<double> FigureStack;    //存储表达式中的操作数
	Stack<char> CharStack;        //存储表达式中的操作符
	CharStack.Add('#');
	static double DotOffset=1;    //小数点的偏移量
	static double Realnumber=0;   //表达式的操作数
	bool Dot=false;                //是否一个数为小数
	bool NegtiveNumber=false;     //是否一个数为负数
	bool IfNumber=false;          //是否进入一个操作数区
	
	int r=0,l=0;                    //左右括号数
	for (int j=0;j<=m_count;j++)
	{
		if(m_expression[j]=='(')
			l++;
		else if(m_expression[j]==')')
			r++;
	}
	
	if(r!=l)
		throw BadInput();    //括号不匹配导致表达式错误
	
	int i=0;
	
	if(m_expression[0]=='-')       //如果“-”在表达式的第一位则必是负号的标志
	{
		NegtiveNumber=true;
		i++;
	}
	for (i;i<=m_count;i++)         //遍历表达式
	{
		if ((i>=1&&m_expression[i-1]=='(')&&m_expression[i]=='-')  //负数的第二个标志：在”（“的比为负数
		{
			NegtiveNumber=true;
			continue;
		}
		
		if ((m_expression[i]>='0'&&m_expression[i]<='9')||m_expression[i]=='.')        //操作数的情况
		{
			if(m_expression[i]=='.')
				Dot=true;
			else
			{
				IfNumber=true;
				double temp=m_expression[i]-'0';                       //字符转化成数
				if(Dot)                                                //小数的处理情况
				{
					DotOffset/=10;
					Realnumber+=temp*DotOffset;       
				}
				else                                                     //整数的处理情况
					Realnumber=Realnumber*10+temp;
				
			}
		}
		else
		{
			if(IfNumber)                                          //把操作数压入栈中
			{
				if(NegtiveNumber)
					Realnumber=-Realnumber;
				FigureStack.Add(Realnumber);
				Dot=false;                                           //重置条件
				DotOffset=1;
				Realnumber=0;
				IfNumber=false;
				NegtiveNumber=false;
			}
			                                               //对字符的处理
			
				char temp1;
Mark:				CharStack.Delete(temp1);
						char GetResult=Judge(temp1,m_expression[i]);  //求值的运算
					
					switch(GetResult)
					{
					case '<':
						double NO1,NO2;
						if(FigureStack.IsEmpty())      //表达式出错
							throw NoMem();
						FigureStack.Delete(NO2);
						if(FigureStack.IsEmpty())      //表达式出错
							throw NoMem();
						FigureStack.Delete(NO1);
						PushToStack(NO1,NO2,temp1,FigureStack);
						goto Mark;                                   //目前字符进行下一次的比较
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
	FigureStack.Delete(m_result);                                   //得到最后结果
}

void Calculator::OutResult()                                           //结果的输出
{
	cout<<"表达式结果是："<<m_result;
	cout<<endl;
}

#endif
// 表达式求值1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include "Caculate.h"
using namespace std;

int main(int argc, char* argv[])
{
	Calculator Test;
	Test.Input();
	Test.DoOperator();
	Test.OutResult();
	return 0;
}


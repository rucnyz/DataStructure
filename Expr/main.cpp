#include "Expr.h"

vector<pair<string, string> > func;

int expr()
{
	string expr;
	cout << "请输入表达式:" << endl;
	getline(cin, expr);
	if (expr == "quit")
	{
		return 0;
	}
	string num;
	double temp = 0;
	int a = preProcess(expr, temp);
	if (a == DEFINITION) //处理def和run
	{
		return 1;
	}
	else if (a == RUN)
	{
		process(expr, RUN, temp);
	}
	else
	{
		process(expr, NORMAL, 0);
	}
	return 1;
}

int matrix()
{

	return 1;
}

int main()
{
	int flag = 1;
	while (flag == 1)
	{
		string a;
		cout << "请问您进行表达式运算还是矩阵运算，表达式运算请输入1，矩阵运算请输入2" << endl;
		getline(cin, a);
		if (a[0] == '1')
		{
			cout << "您正在使用表达式计算系统" << endl;
			cout << "自定义变量请使用字母与其他符号，不要使用数字。" << endl;
			cout << "定义方程请使用DEF, 计算方程请使用RUN。" << endl;
			cout << "输入quit退出程序" << endl;
			while (expr())
			{
			}
		}
		else if (a[0] == '2')
		{
			flag = matrix();
		}
		else if (a == "quit")
		{
			cout << "感谢您的使用!" << endl;
			flag = 0;
		}
		else
		{
			cout << "您的输入有误！" << endl;
		}
		cout << "==============================" << endl;
	}
	return 0;
}

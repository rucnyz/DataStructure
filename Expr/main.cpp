#include "Expr.h"

int expr()
{
	string expr;
	cout << "请输入表达式:" << endl;
	cout << "(自定义变量请使用字母与其他符号，不要使用数字。输入quit退出程序)" << endl;
	getline(cin, expr);
	if (expr == "quit")
	{
		return 0;
	}

	double result = 0;
	vector<string> var;
	if (findLocalVar(expr, var))
	{
		string x;
		while (true)
		{
			string tmp = expr;
			//一次计算
			for (auto i = var.begin(); i < var.end(); ++i)
			{
				string temp;
				cout << "请输入" << *i << "的值:" << endl;
				getline(cin, temp);
				//全体替换
				while (true)
				{
					size_t index = tmp.find(*i);
					if (index == 0xFFFFFFFFFFFFFFFF)
					{
						break;
					}
					//用于在ax的中间插入*
					if (index > 0 &&
					    tmp[index - 1] >= 48 && tmp[index - 1] <= 57)
					{
						temp.insert(0, "*");
						tmp.replace(index, (*i).size(), temp);
						//去掉乘号
						temp = temp.substr(1, temp.size() - 1);
					}
					else
					{
						tmp.replace(index, (*i).size(), temp);
					}
				}
			}
			if (calExpr(tmp, result) == ERROR)
			{
				cout << "表达式输入有误！" << endl;
			}
			else
			{
				cout << "结果是：" << endl;
				cout << result << endl;
			}
			cout << "请选择是否更换变量进行计算(是请输入1，否则输入0,退出请输入quit):" << endl;
			getline(cin, x);
			if (x[0] == '0')
			{
				break;
			}
			else if (x == "quit")
			{
				return 0;
			}
		}
	}
	else if (calExpr(expr, result) == ERROR)
	{
		cout << "表达式输入有误！" << endl;
	}
	else
	{
		cout << "结果是：" << endl;
		cout << result << endl;
	}
	return 1;
}

int main()
{
	int flag = 1;
	while (flag == 1)
	{
		cout << "请问您是" <<endl;
		flag = expr();
		cout << "==============================" << endl;
	}
	return 0;
}

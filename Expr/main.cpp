#include <iostream>
#include <stack>
#include <cmath>
#include <vector>

#define ERROR 1
#define NORMAL 2
using namespace std;

/// 比较运算符的优先性
/// \param a 第一个运算符
/// \param b 第二个运算符
/// \return 如果第一个优先于第二个，返回true;否则返回false.
bool cmp(char &a, char &b)
{
	//到达末尾
	if (b == '#')
	{
		return true;
	}
	//左括号入栈前优先级最高；入栈后优先级最低
	if (a == '(' || b == '(')
	{
		return false;
	}
	//遇到右括号的情况
	if (b == ')')
	{
		return true;
	}
	//最大的情况
	if (a == '^')
	{
		return true;
	}
	else if (a == '*' || a == '/' || a == '%')
	{
		if (b == '^')
		{
			return false;
		}
		else
		{
			return true;
		}
	}
	else if (a == '+' || a == '-')
	{
		if (b == '+' || b == '-')
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	return true;
}

/// 根据传入的操作符计算结果
/// \param a
/// \param b
/// \param op
/// \return
template<typename T>
T calculate(T a, T b, char &op)
{
	if (op == '+')
	{
		return a + b;
	}
	else if (op == '-')
	{
		return a - b;
	}
	else if (op == '*')
	{
		return a * b;
	}
	else if (op == '/')
	{
		return a / b;
	}
	else if (op == '%')
	{
		return (int) a % (int) b;
	}
	else
	{
		return pow(a, b);
	}
}

/// 检验括号是否匹配
/// \param expr
/// \return 如果匹配返回true，否则返回false
bool isValidExpr(string &expr)
{
	stack<char> brackets;
	for (auto i = expr.begin(); i < expr.end(); ++i)
	{
		if (*i == '(')
		{
			brackets.push(*i);
		}
		else if (*i == ')')
		{
			if (brackets.empty())
			{
				return false;
			}
			else
			{
				brackets.pop();
			}
		}
	}
	if (brackets.empty())
	{
		return true;
	}
	else
	{
		return false;
	}
}

/// 找到表达式中的本地变量
/// \param expr
/// \param LocalVar
/// \return
bool findLocalVar(string &expr, vector<string> &LocalVar)
{
	string temp;
	string var;
	for (auto i = expr.begin(); i < expr.end(); ++i)
	{
		if (((*i) >= 48 && (*i) <= 57) || (*i == 46) ||
		    *i == '+' || *i == '-' || *i == '*' ||
		    *i == '/' || *i == '^' || *i == '#' ||
		    *i == '%' || *i == '(' || *i == ')')
		{
			if (!var.empty())
			{
				LocalVar.push_back(var);
				var.clear();
			}

		}
		else
		{
			var.push_back(*i);
		}
	}
	if (!var.empty())
	{
		LocalVar.push_back(var);
		var.clear();
	}
	if (!LocalVar.empty())
	{
		return true;
	}
	else
	{
		return false;
	}
}

/// 计算表达式
/// \param expr
/// \param result
/// \return
int calExpr(string &expr, double &result)
{
	if (!isValidExpr(expr))
	{
		return ERROR;
	}
	expr.append("#");
	string num;
	stack<double> nums;
	stack<char> operands;
	for (auto i = expr.begin(); i < expr.end(); ++i)
	{
		if (*i == ' ')
		{
			continue;
		}
		if (((*i) >= 48 && (*i) <= 57) || (*i == 46))
		{
			num.append(i, i + 1);
		}
		else if (*i == '+' || *i == '-' || *i == '*'
		         || *i == '/' || *i == '^' || *i == '#'
		         || *i == '%' || *i == '(' || *i == ')')
		{
			if (!num.empty())
			{
				nums.push(stof(num));
				num.clear();
			}
			if (operands.empty())
			{
				if (*i == '#')
				{
					break;
				}
				operands.push(*i);
			}
			else
			{
				char tmp = operands.top();
				//括号汇合
				if (tmp == '(' && *i == ')')
				{
					operands.pop();
					continue;
				}
				if (cmp(tmp, *i))
				{
					double b = nums.top();
					nums.pop();
					double a = nums.top();
					nums.pop();
					result = calculate(a, b, tmp);
					nums.push(result);
					i--;
					operands.pop();
					continue;
				}
				else
				{
					operands.push(*i);
				}
			}
		}
		else
		{
			return ERROR;
		}
	}
	if (!nums.empty())
	{
		result = nums.top();
	}
	return NORMAL;

}

int main()
{
	int flag = 1;
	while (flag == 1)
	{
		string expr;
		cout << "请输入表达式:" << endl;
		cout << "(自定义变量请使用字母与其他符号，不要使用数字。)" << endl;
		cout << "输入quit退出程序" << endl;
		getline(cin, expr);
		if (expr == "quit")
		{
			flag = 0;
			continue;
		}

		double result = 0;
		vector<string> var;
		if (findLocalVar(expr, var))
		{
			for (auto i = var.begin(); i < var.end(); ++i)
			{
				string temp;
				cout << "请输入" << *i << "的值:" << endl;
				getline(cin, temp);
				//用于在ax的中间插入*
				if (expr.find(*i) > 0 &&
				    expr[expr.find(*i) - 1] >= 48 && expr[expr.find(*i) - 1] <= 57)
				{
					temp.insert(0, "*");
				}
				//替换
				expr.replace(expr.find(*i), (*i).size(), temp);
			}
		}
		cout << "结果是：" << endl;
		if (calExpr(expr, result) == ERROR)
		{
			cout << "表达式输入有误！" << endl;
		}
		else
		{
			cout << result << endl;
		}

	}
	return 0;
}

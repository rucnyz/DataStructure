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
/// \return 计算结果
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
/// \param LocalVar 将本地变量以字符传给它
/// \return 返回是否找到
bool findLocalVar(string &expr, vector<string> &LocalVar)
{
	string temp;
	string var;
	int flag;
	for (auto i = expr.begin(); i < expr.end(); ++i)
	{
		if (((*i) >= 48 && (*i) <= 57) || (*i == 46) ||
		    *i == '+' || *i == '-' || *i == '*' ||
		    *i == '/' || *i == '^' || *i == '#' ||
		    *i == '%' || *i == '(' || *i == ')')
		{
			if (!var.empty())
			{
				if ((*i) >= 48 && (*i) <= 57)
				{
					var.push_back(*i);
					continue;
				}
				flag = 0;
				for (auto j = LocalVar.begin(); j < LocalVar.end(); ++j)
				{
					if (*j == var)
					{
						flag = 1;
						break;
					}
				}
				if (flag == 0)
				{
					LocalVar.push_back(var);
				}
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
		flag = 0;
		for (auto j = LocalVar.begin(); j < LocalVar.end(); ++j)
		{
			if (*j == var)
			{
				flag = 1;
				break;
			}
		}
		if (flag == 0)
		{
			LocalVar.push_back(var);
		}
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
/// \param result 运算结果
/// \return 判断表达式是否出错
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
		cout << "(自定义变量请使用字母与其他符号，不要使用数字。输入quit退出程序)" << endl;
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
		cout << "==============================" << endl;
	}
	return 0;
}

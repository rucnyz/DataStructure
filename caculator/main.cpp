#include <iostream>
#include "LinearList.h"
#include "LinkList.h"

#define QUIT 2
#define ERROR 1
#define NORMAL 3
using namespace std;

int vectorCalculation()
{
	LinearList First{}, Second{}, Result{};
	string Expression;
	cout << "请选择操作类型" << endl;
	cout << "('+'为加法,'-'为减法,'cos'为计算余弦):" << endl;
	getline(cin, Expression);
	if (Expression[0] == 'q')
	{
		return QUIT;
	}
	else if (Expression[0] == '+' || Expression[0] == '-' || Expression[0] == 'c')
	{

		string firstArr;
		string secondArr;
		cout << "请输入第一个向量(请使用,或;进行分割):" << endl;
		getline(cin, firstArr);
		//firstArr = "1,2,3,4,5";
		cout << "请输入第二个向量(请使用,或;进行分割):" << endl;

		getline(cin, secondArr);
		//secondArr = "2,3,4,5,6";

		initList(First, firstArr, 1);
		initList(Second, secondArr, 1);

		if (First.length != Second.length)
		{
			return ERROR;
		}
		if (Expression[0] == 'c')
		{
			double result = cos(First, Second);
			cout << "结果是:" << endl;
			cout << result << endl;
			cout << endl;
		}
		else
		{
			Result = vecCal(First, Second, Expression[0]);

			cout << "结果是:" << endl;
			vecDisplay(Result);
			cout << endl;
		}
	}
	else
	{
		return ERROR;
	}
	return NORMAL;
}

int polyCalculation()
{
	string Expression;
	string flag = "1";
	cout << "请选择:使用顺序表请输入1,链表请输入2:" << endl;
	getline(cin, flag);
	if (flag[0] == 'q')
	{
		return QUIT;
	}
	else if (flag[0] != '1' && flag[0] != '2')
	{
		return ERROR;
	}

	cout << "请选择操作类型" << endl;
	cout << "('+'为加法,'-'为减法,'*'为乘法,'g'为求导数):" << endl;
	getline(cin, Expression);
	if (Expression[0] == 'q')
	{
		return QUIT;
	}
	else if (Expression[0] == '+'
	         || Expression[0] == '-'
	         || Expression[0] == '*')
	{
		string firstArr;
		string secondArr;
		cout << "请输入第一个多项式:(请使用x作为变量且按照从大到小的顺序)" << endl;
		getline(cin, firstArr);
		//firstArr = "x^4+x^2+3";
		cout << "请输入第二个多项式:(请使用x作为变量且按照从大到小的顺序)" << endl;

		getline(cin, secondArr);
		//secondArr = "x^4+x^1+4";
		if (flag[0] == '1')
		{
			LinearList Second{};
			LinearList Result{};
			LinearList First{};

			initList(First, firstArr, 2);
			initList(Second, secondArr, 2);


			Result = polyCal(First, Second, Expression[0]);


			cout << "结果是:" << endl;
			polyDisplay(Result);
			cout << endl;
		}
		else if (flag[0] == '2')
		{
			LinkList *first = nullptr;
			LinkList *second = nullptr;
			LinkList *result = nullptr;
			LinkList *firstHead;
			LinkList *secondHead;
			LinkList *resultHead;

			//给链表开辟空间
			init(firstHead);
			init(secondHead);
			init(resultHead);

			//拼接两个链表的头结点
			init(first);
			firstHead->next = first;
			init(second);
			secondHead->next = second;

			//拼接结果的头结点
			init(result);
			resultHead->next = result;
			//将字符串的内容写入链表
			initList(first, firstArr);
			initList(second, secondArr);

			//计算
			firstHead = firstHead->next;
			secondHead = secondHead->next;
			polyCal(firstHead, secondHead, result, Expression[0]);

			//输出结果
			cout << "结果是:" << endl;
			polyDisplay(resultHead);
			cout << endl;
		}
	}
	else if (Expression[0] == 'g')
	{
		string str;
		cout << "请输入多项式:" << endl;
		getline(cin, str);
		if (flag[0] == '1')
		{
			LinearList input{}, result{};
			initList(input, str, 2);
			cout << "其导数为:" << endl;
			result = grad(input);
			polyDisplay(result);
			cout << endl;
		}
		else if (flag[0] == '2')
		{
			LinkList *inputHead = nullptr;
			LinkList *input = nullptr;
			init(inputHead);
			init(input);
			inputHead->next = input;
			initList(input, str);
			input = inputHead->next;
			grad(input);
			cout << "其导数为:" << endl;
			polyDisplay(inputHead);
			cout << endl;
		}
	}
	else
	{
		return ERROR;
	}
	return NORMAL;
}

int main()
{
	int ret = 1;
	cout << "欢迎使用本程序！您可以在任何时候按下'q'退出程序" << endl;
	while (ret == 1)
	{
		string cal;

		cout << "-----------------------------------" << endl;
		cout << "请选择进行向量计算还是多项式计算" << endl;
		cout << "(向量计算请输入1,多项式计算请输入2)" << endl;
		getline(cin, cal);
		//向量计算
		if (cal[0] == '1')
		{
			int x = vectorCalculation();
			if (x == QUIT)
			{
				ret = 0;
			}
			else if (x == ERROR)
			{
				cout << "您的输入有误！请重新输入" << endl;
				continue;
			}
		}
			//多项式计算
		else if (cal[0] == '2')
		{
			int x = polyCalculation();
			if (x == QUIT)
			{
				ret = 0;
			}
			else if (x == ERROR)
			{
				cout << "您的输入有误！请重新输入" << endl;
				continue;
			}
		}
			//退出程序
		else if (cal[0] == 'q')
		{
			ret = 0;
		}
			//输入错误
		else
		{
			cout << "您的输入有误！请重新输入" << endl;
		}

	}
	cout << "感谢您的使用!" << endl;
	return 0;
}

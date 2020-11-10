#include "Expr.h"
#include "Matrix.h"

vector<pair<string, string> > func;

int Expr()
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

int mat()
{
	string expr, str1, str2;
	Matrix mat1;
	Matrix mat2;
	cout << "请决定运算类型:" << endl;
	cout << "加法输入1,减法输入2,点乘输入3,除法输入4,矩阵乘法输入5," << endl;
	cout << "求行列式输入6,求矩阵特征值输入7,求矩阵的逆输入8" << endl;
	getline(cin, expr);
	if (expr == "quit")
	{
		return 0;
	}
	switch (expr[0])
	{
		case '1':
			cout << "请输入第一个矩阵:" << endl;
			getline(cin, str1);
			cout << "请输入第二个矩阵:" << endl;
			getline(cin, str2);
			mat1 = processInput(str1);
			mat2 = processInput(str2);
			cout << "您输入的矩阵是:" << endl;
			cout << mat1;
			cout << mat2;
			cout << "结果是:" << endl;
			cout << mat1 + mat2;
			break;
		case '2':
			cout << "请输入第一个矩阵:" << endl;
			getline(cin, str1);
			cout << "请输入第二个矩阵:" << endl;
			getline(cin, str2);
			mat1 = processInput(str1);
			mat2 = processInput(str2);
			cout << "您输入的矩阵是:" << endl;
			cout << mat1;
			cout << mat2;
			cout << "结果是:" << endl;
			cout << mat1 - mat2;
			break;
		case '3':
			cout << "请输入第一个矩阵:" << endl;
			getline(cin, str1);
			cout << "请输入第二个矩阵:" << endl;
			getline(cin, str2);
			mat1 = processInput(str1);
			mat2 = processInput(str2);
			cout << "您输入的矩阵是:" << endl;
			cout << mat1;
			cout << mat2;
			cout << "结果是:" << endl;
			cout << mat1.mul(mat2);
			break;
		case '4':
			cout << "请输入第一个矩阵:" << endl;
			getline(cin, str1);
			cout << "请输入第二个矩阵:" << endl;
			getline(cin, str2);
			mat1 = processInput(str1);
			mat2 = processInput(str2);
			cout << "您输入的矩阵是:" << endl;
			cout << mat1;
			cout << mat2;
			cout << "结果是:" << endl;
			cout << mat1 / mat2;
			break;
		case '5':
			cout << "请输入第一个矩阵:" << endl;
			getline(cin, str1);
			cout << "请输入第二个矩阵:" << endl;
			getline(cin, str2);
			mat1 = processInput(str1);
			mat2 = processInput(str2);
			cout << "您输入的矩阵是:" << endl;
			cout << mat1;
			cout << mat2;
			cout << "结果是:" << endl;
			cout << mat1 * mat2 << endl;
			break;
		case '6':
			cout << "请输入矩阵:" << endl;
			getline(cin, str1);
			mat1 = processInput(str1);
			cout << "您输入的矩阵是:" << endl;
			cout << mat1;
			cout << "结果是:" << endl;
			cout << mat1.getDet() << endl;
			break;
		case '7':
		{
			cout << "请输入矩阵:" << endl;
			getline(cin, str1);
			mat1 = processInput(str1);
			cout << "您输入的矩阵是:" << endl;
			cout << mat1;
			cout << "结果是:" << endl;
			double *values;
			int a = mat1.eigenvalues(values);
			for (int i = 0; i < a; ++i)
			{
				cout << values[i] << " ";
			}
			cout << endl;
			break;
		}
		case '8':
			cout << "请输入矩阵:" << endl;
			getline(cin, str1);
			mat1 = processInput(str1);
			cout << "您输入的矩阵是:" << endl;
			cout << mat1;
			cout << "结果是:" << endl;
			cout << mat1.inv_LU();
			break;
		default:
			cout << "您的选择有误!" << endl;
			break;
	}
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
		//表达式计算
		if (a[0] == '1')
		{
			cout << "您正在使用表达式计算系统" << endl;
			cout << "自定义变量请使用字母与其他符号，不要使用数字。" << endl;
			cout << "定义方程请使用DEF, 计算方程请使用RUN。" << endl;
			cout << "输入quit退出程序" << endl;
			cout << endl;
			//内部循环
			while (Expr())
			{
				cout << "==============================" << endl;
			}
		}
			//矩阵运算
		else if (a[0] == '2')
		{
			cout << "您正在使用矩阵运算系统" << endl;
			cout << "请使用','分割行，使用';'分割列" << endl;
			cout << "一个简单的例子'1,2;3,4'   其结果为:" << endl;
			cout << "1 2" << endl;
			cout << "3 4" << endl;
			cout << "输入quit退出程序" << endl;
			cout << endl;
			while (mat())
			{
				cout << "==============================" << endl;
			}
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

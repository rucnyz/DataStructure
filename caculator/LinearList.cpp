/*
 * -*- coding: utf-8 -*-
 * @Time    : 2020/10/5 18:36
 * @Author  : nieyuzhou
 * @File    : LinearList.h/cpp
 * @Software: CLion
 */
#include "LinearList.h"

template<typename T>
struct cmp
{
	//重载 () 运算符
	bool operator()(T a, T b)
	{
		return (a > b);
	}
};

template<>
struct cmp<Data>
{
	bool operator()(Data a, Data b)
	{
		return (a.power < b.power);
	}
};

void initList(LinearList &L, string &expression, int a)
{
	vector<string> tmp;
	if (a == 2)
	{
		tmp = split(expression, '+', '-');
		L.length = tmp.size();
		L.data = (Data *) malloc(L.length * (sizeof(int) + sizeof(int *)));
		parser(tmp, L);
	}
	else
	{
		tmp = split(expression, ',', ';');
		L.length = tmp.size();
		L.data = (Data *) malloc(L.length * (sizeof(int) + sizeof(int *)));
		int j = 0;
		for (auto i = tmp.begin(); i < tmp.end(); ++i)
		{
			L.data[j].parameter = stoi(*i);
			j++;
		}
	}
}

LinearList polyCal(LinearList &first, LinearList &second, char c)
{
	LinearList result{};
	if (c == '*')
	{
		return polyPlus(first, second);
	}
	result.data = (Data *) malloc((first.length + second.length) * sizeof(first.data[0]));
	int i = 0, j = 0, k = 0, flag = 0;
	while (flag != 1)
	{
		//前者到达末端
		if (i == first.length)
		{
			if (c == '+')
			{
				result.data[k].parameter = second.data[j].parameter;
			}
			else if (c == '-')
			{
				result.data[k].parameter = -second.data[j].parameter;
			}
			result.data[k].power = second.data[j].power;
			k++;
			j++;
		}//后者到达末端
		else if (j == second.length)
		{
			result.data[k].parameter = first.data[i].parameter;
			result.data[k].power = first.data[i].power;
			k++;
			i++;
		}//均未到达末端，则比较指数，较大者被存入结果，并后移；
		else if (first.data[i].power != second.data[j].power)
		{
			if (first.data[i].power > second.data[j].power)
			{

				result.data[k].parameter = first.data[i].parameter;
				result.data[k].power = first.data[i].power;
				k++;
				i++;


			}
			else
			{
				if (c == '+')
				{
					result.data[k].parameter = second.data[j].parameter;
				}
				else if (c == '-')
				{
					result.data[k].parameter = -second.data[j].parameter;
				}
				result.data[k].power = second.data[j].power;

				k++;
				j++;


			}
		}//均未达到末端，两者指数相同，计算后存入结果；均后移
		else
		{
			result.data[k].power = first.data[i].power;
			if (c == '+')
			{
				result.data[k].parameter = first.data[i].parameter + second.data[j].parameter;
			}
			else if (c == '-')
			{
				result.data[k].parameter = first.data[i].parameter - second.data[j].parameter;
			}
			k++;
			j++;
			i++;

		}

		if (i == first.length && j == second.length)
		{
			flag = 1;
		}
	}
	result.length = k;
	return result;
}

LinearList vecCal(LinearList &first, LinearList &second, char c)
{
	LinearList result{};
	//之前已有判断first和second是否等长
	result.length = first.length;
	result.data = (Data *) malloc((result.length) * sizeof(first.data[0]));
	if (c == '+')
	{
		for (int i = 0; i < result.length; ++i)
		{
			result.data[i].parameter = first.data[i].parameter + second.data[i].parameter;
		}
	}
	else if (c == '-')
	{
		for (int i = 0; i < result.length; ++i)
		{
			result.data[i].parameter = first.data[i].parameter - second.data[i].parameter;
		}
	}
	return result;
}

double cos(LinearList &first, LinearList &second)
{
	double d;
	double sum = 0;
	double A = 0, B = 0;
	for (int i = 0; i < first.length; ++i)
	{
		sum += (double) first.data[i].parameter * second.data[i].parameter;
		A += (double) first.data[i].parameter * first.data[i].parameter;
		B += (double) second.data[i].parameter * second.data[i].parameter;
	}
	d = sum / (sqrt(fabs(A)) * sqrt(fabs(B)));
	return d;

}

LinearList polyPlus(LinearList &first, LinearList &second)
{
	LinearList result{};
	result.data = (Data *) malloc((first.length * second.length) * sizeof(first.data[0]));
	//使用优先队列
	priority_queue<Data, vector<Data>, cmp<Data> > temp;

	for (int i = 0; i < first.length; ++i)
	{
		for (int j = 0; j < second.length; ++j)
		{
			Data tmp{};
			tmp.power = first.data[i].power + second.data[j].power;
			tmp.parameter = first.data[i].parameter * second.data[j].parameter;
			temp.push(tmp);
		}
	}

	result.length = temp.size();

	int i;
	for (i = 0; !temp.empty(); ++i)
	{
		if (i > 0 && temp.top().power == result.data[i - 1].power)
		{
			result.data[i - 1].parameter += temp.top().parameter;
			i--;
			temp.pop();
			continue;
		}
		result.data[i].parameter = temp.top().parameter;
		result.data[i].power = temp.top().power;
		temp.pop();
	}
	result.length = i;
	return result;
}


LinearList grad(LinearList &input)
{
	LinearList result{};
	result.length = input.length;
	result.data = (Data *) malloc(result.length * sizeof(input.data[0]));
	if (input.length == 1 && input.data[0].power == 0)
	{
		result.data[0].parameter = 0;
		result.data[0].power = 0;
		return result;
	}
	for (int i = 0; i < input.length; ++i)
	{
		if (input.data[i].power == 0)
		{
			result.length--;
			break;
		}
		result.data[i].power = input.data[i].power - 1;
		result.data[i].parameter = input.data[i].parameter * input.data[i].power;
	}
	return result;
}

/*
 * -*- coding: utf-8 -*-
 * @Time    : 2020/10/5 18:44
 * @Author  : nieyuzhou
 * @File    : LinkList.h/cpp
 * @Software: CLion
 */
#include "LinkList.h"

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
struct cmp<LinkList>
{
	bool operator()(LinkList a, LinkList b)
	{
		return (a.data.power < b.data.power);
	}
};

void init(LinkList *&L)
{
	//初始化结点
	L = (LinkList *) malloc(sizeof(LinkList));
	L->next = nullptr;

}


void initList(LinkList *&L, string &expression)
{
	vector<string> tmp;
	tmp = split(expression, '+', '-');
	parser(tmp, L);
}

void polyCal(LinkList *&first, LinkList *&second, LinkList *&result, char c)
{
	if (c == '*')
	{
		polyPlus(first, second, result);
		return;
	}
	while (true)
	{
		//前者到达末端
		if (first == nullptr)
		{
			if (c == '+')
			{
				result->data.parameter = second->data.parameter;
			}
			else if (c == '-')
			{
				result->data.parameter = -second->data.parameter;
			}
			result->data.power = second->data.power;
			second = second->next;
		}//后者到达末端
		else if (second == nullptr)
		{
			result->data.parameter = first->data.parameter;
			result->data.power = first->data.power;
			first = first->next;
		}//均未到达末端，则比较指数，较大者被存入结果，并后移；
		else if (first->data.power != second->data.power)
		{
			if (first->data.power > second->data.power)
			{

				result->data.parameter = first->data.parameter;
				result->data.power = first->data.power;
				first = first->next;


			}
			else
			{
				if (c == '+')
				{
					result->data.parameter = second->data.parameter;
				}
				else if (c == '-')
				{
					result->data.parameter = -second->data.parameter;
				}
				result->data.power = second->data.power;

				second = second->next;


			}
		}//均未达到末端，两者指数相同，计算后存入结果；均后移
		else
		{
			result->data.power = first->data.power;
			if (c == '+')
			{
				result->data.parameter = first->data.parameter + second->data.parameter;
			}
			else if (c == '-')
			{
				result->data.parameter = first->data.parameter - second->data.parameter;
			}
			first = first->next;
			second = second->next;

		}
		if (first == nullptr && second == nullptr)
		{
			break;
		}
		init(result->next);
		result = result->next;
	}
}


void grad(LinkList *&input)
{
	if (input->data.power == 0)
	{
		input->data.parameter = 0;
		return;
	}
	input->data.parameter = input->data.parameter * input->data.power;
	input->data.power = input->data.power - 1;
	while (input->next != nullptr)
	{
		if (input->next->data.power == 0)
		{
			input->next = nullptr;
			break;
		}
		input = input->next;
		input->data.parameter = input->data.parameter * input->data.power;
		input->data.power = input->data.power - 1;
	}
}


void polyPlus(LinkList *&first, LinkList *&second, LinkList *&result)
{
	//使用优先队列
	priority_queue<LinkList, vector<LinkList>, cmp<LinkList> > temp;
	LinkList *secondHead = second;
	while (first != nullptr)
	{
		second = secondHead;
		while (second != nullptr)
		{
			LinkList *tmp = nullptr;
			init(tmp);
			tmp->data.power = first->data.power + second->data.power;
			tmp->data.parameter = first->data.parameter * second->data.parameter;
			temp.push(*tmp);
			second = second->next;
		}
		first = first->next;
	}
	int tmpPower = 0, tmpParameter = 0;
	result->data.parameter = temp.top().data.parameter;
	result->data.power = temp.top().data.power;
	tmpPower = result->data.power;
	tmpParameter = result->data.parameter;
	temp.pop();
	while (!temp.empty())
	{
		if (temp.top().data.power == tmpPower)
		{
			result->data.parameter = tmpParameter + temp.top().data.parameter;
			tmpParameter = result->data.parameter;
			temp.pop();
			continue;
		}
		init(result->next);
		result = result->next;
		result->data.parameter = temp.top().data.parameter;
		result->data.power = temp.top().data.power;
		tmpPower = result->data.power;
		tmpParameter = result->data.parameter;
		temp.pop();
	}
}
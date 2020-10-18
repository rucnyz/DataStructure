/*
 * -*- coding: utf-8 -*-
 * @Time    : 2020/10/5 0:16
 * @Author  : nieyuzhou
 * @File    : utilities.h/cpp
 * @Software: CLion
 */
#include "utilities.h"

///
/// \param expression
/// \param c1
/// \param c2
/// \return
vector<string> split(string &expression, char c1, char c2)
{
	vector<string> result;
	string tmp;

	for (auto i = expression.begin(); i < expression.end(); ++i)
	{
		if (*i == ' ')
		{
			continue;
		}
		if (*i == c1 || *i == c2)
		{
			if (!tmp.empty())
			{
				result.push_back(tmp);
			}
			tmp.clear();
			if (*i == '-')
			{
				tmp.append("-");
			}
			continue;
		}
		tmp.append(i, i + 1);

	}

	if (!tmp.empty())
	{
		result.push_back(tmp);
	}

	return result;
}

/// 分解单个算式
/// \param splited
/// \param mainList
void parser(vector<string> &splited, LinearList &mainList)
{

	for (auto i = splited.begin(); i < splited.end(); ++i)
	{
		vector<string> tmp;
		int parameter = 0;
		int power = 0;
		//常数项情况
		if (i->find('x') == -1)
		{
			parameter = stoi(*i);
			power = 0;
		}
			//一次项及以上的情况
		else
		{

			tmp = split(*i, 'x');
			//正常情况
			if (tmp.size() == 2)
			{
				//-x...的情况
				if (tmp[0].size() == 1 && *(tmp[0].begin()) == '-')
				{
					parameter = -1;
					power = stoi(tmp[1].substr(1));
				}
				else
				{
					parameter = stoi(tmp[0]);
					power = stoi(tmp[1].substr(1));
				}
			}
				//x^...或...x的情况
			else if (tmp.size() == 1)
			{
				//前一种情况
				if (*tmp[0].begin() == '^')
				{
					parameter = 1;
					power = stoi(tmp[0].substr(1));
				}
				else//后一种情况
				{
					parameter = stoi(tmp[0]);
					power = 1;
				}
			}
				//x的情况
			else if (tmp.empty())
			{
				parameter = 1;
				power = 1;
			}
		}

		mainList.data[i - splited.begin()].parameter = parameter;
		mainList.data[i - splited.begin()].power = power;
	}
}

///
/// \param splited
/// \param mainList


void parser(vector<string> &splited, LinkList *&mainList)
{
	for (auto i = splited.begin(); i < splited.end(); ++i)
	{
		vector<string> temp;
		int parameter = 0;
		int power = 0;
		//常数项情况
		if (i->find('x') == -1)
		{
			parameter = stoi(*i);
			power = 0;
		}
			//一次项及以上的情况
		else
		{
			temp = split(*i, 'x');
			//正常情况
			if (temp.size() == 2)
			{
				//-x...的情况
				if (temp[0].size() == 1 && *(temp[0].begin()) == '-')
				{
					parameter = -1;
					power = stoi(temp[1].substr(1));
				}
				else
				{
					parameter = stoi(temp[0]);
					power = stoi(temp[1].substr(1));
				}
			}
				//x^...或...x的情况
			else if (temp.size() == 1)
			{
				//前一种情况
				if (*temp[0].begin() == '^')
				{
					parameter = 1;
					power = stoi(temp[0].substr(1));
				}
				else//后一种情况
				{
					parameter = stoi(temp[0]);
					power = 1;
				}
			}
				//x的情况
			else if (temp.empty())
			{
				parameter = 1;
				power = 1;
			}
		}
		mainList->data.parameter = parameter;
		mainList->data.power = power;
		if (mainList->next == nullptr && i < splited.end() - 1)
		{
			mainList->next = (LinkList *) malloc(sizeof(LinkList));
			mainList = mainList->next;
			mainList->next = nullptr;
		}
	}
}

///
/// \param input
void polyDisplay(LinearList &input)
{
	int flag = 1;
	for (int i = 0; i < input.length; ++i)
	{
		//判断结果是否为'1'(特殊情况)
		if (input.data[i].parameter == 1 && input.data[i].power == 0)
		{
			cout << "1";
		}
		else if (input.data[i].parameter == -1 && input.data[i].power == 0)
		{
			cout << "-1";
		}
		else
		{
			//判断此项是否已不存在
			if (input.data[i].parameter == 0)
			{
				continue;
			}
			//是否省略系数
			if (input.data[i].parameter != 1)
			{
				if (input.data[i].parameter == -1)
				{
					cout << "-";
				}
				else
				{
					cout << input.data[i].parameter;
				}
			}
			//是否省略指数
			if (input.data[i].power == 1)
			{
				cout << "x";
			}
			else if (input.data[i].power > 1)
			{
				cout << "x^" << input.data[i].power;
			}
		}
		if (i < input.length - 1 && input.data[i + 1].parameter > 0)
		{
			cout << "+";
		}
		flag = 0;
	}
	if (flag)
	{
		cout << "0";
	}
}

///
/// \param input
void polyDisplay(LinkList *&input)
{
	int flag = 1;
	while (input->next != nullptr)
	{
		input = input->next;
		if (input->data.parameter == 1 && input->data.power == 0)
		{
			cout << "1";
		}
		else if (input->data.parameter == -1 && input->data.power == 0)
		{
			cout << "-1";
		}
		else
		{
			//判断此项是否已不存在
			if (input->data.parameter == 0)
			{
				continue;
			}
			//是否省略系数
			if (input->data.parameter != 1)
			{
				if (input->data.parameter == -1)
				{
					cout << "-";
				}
				else
				{
					cout << input->data.parameter;
				}
			}
			//是否省略指数
			if (input->data.power == 1)
			{
				cout << "x";
			}
			else if (input->data.power > 1)
			{
				cout << "x^" << input->data.power;
			}
		}
		if (input->next != nullptr && input->next->data.parameter > 0)
		{
			cout << "+";
		}
		flag = 0;
	}
	if (flag)
	{
		cout << "0";
	}
}

///
/// \param input
void vecDisplay(LinearList &input)
{
	cout << "(";
	for (int i = 0; i < input.length - 1; ++i)
	{
		cout << input.data[i].parameter << ",";
	}
	cout << input.data[input.length - 1].parameter << ")";
}

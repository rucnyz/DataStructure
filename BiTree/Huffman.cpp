/*
 * -*- coding: utf-8 -*-
 * @Time    : 2020/12/4 8:42
 * @Author  : nieyuzhou
 * @File    : Huffman.h/cpp
 * @Software: CLion
 */
#include "Huffman.h"

Huffman::Huffman(int n, map<char, float> &weight) : length(n)
{
	int m = 2 * n - 1;
	// 为赫夫曼树分配一组顺序空间
	hfTree = (HuffmanTree) malloc(m * sizeof(HtNode));
	int i = 0;
	auto p = hfTree;
	// 外部节点初始化，每个结点的左、右孩子为-1
	for (auto w = weight.begin(); i < n; ++i, ++p, ++w)
	{
		*p = {(*w).second, 0, -1, -1, (*w).first};
	}
	// 内部节点初始化
	for (; i < m; ++i, ++p)
	{
		*p = {0, 0, 0, 0, '\0'};
	}
	int s1, s2;
	for (i = n; i < m; ++i)
	{   // 建赫夫曼树
		Select(hfTree, i, s1, s2);

		hfTree[s1].parent = i;
		hfTree[s2].parent = i;
		hfTree[i].leftLink = s1;
		hfTree[i].rightLink = s2;
		hfTree[i].weight = hfTree[s1].weight + hfTree[s2].weight;
		// 取左、右子树根结点权值之和
	}
	//根节点parent为-1
	hfTree[i - 1].parent = -1;
	root = i - 1;
}

Huffman::Huffman() : root(0), length(0), hfTree(nullptr)
{

}

void Huffman::Select(HuffmanTree tree, int i, int &s1, int &s2)
{
	float s1Weight = 100;
	float s2Weight = 110;
	for (int j = 0; j < i; ++j)
	{
		if (tree[j].parent != 0)
		{
			continue;
		}
		//找到两个最小值
		if (tree[j].weight <= min(s1Weight, s2Weight))
		{
			if (s1Weight < s2Weight)
			{
				s2Weight = tree[j].weight;
				s2 = j;
			}
			else
			{
				s1Weight = tree[j].weight;
				s1 = j;
			}
		}
		else if (tree[j].weight <= s2Weight)
		{
			s2 = j;
			s2Weight = tree[j].weight;
		}
		else if (tree[j].weight <= s1Weight)
		{
			s1 = j;
			s1Weight = tree[j].weight;
		}
	}
}

string Huffman::concat(const string &input, map<char, string> &code)
{
	string output;
	for (auto i = input.begin(); i < input.end(); ++i)
	{
		output += code.find(*i)->second;
	}
	return output;
}

string Huffman::decode(string &password)
{
	int k = root;
	string output;
	if (k == 0)
	{
		for (auto i = password.begin(); i < password.end(); ++i)
		{
			if (*i == '0')
			{
				output += hfTree[k].ch;
			}
		}
		return output;
	}
	for (auto i = password.begin(); i < password.end(); ++i)
	{
		switch (*i)
		{
			case '1':
			{
				k = hfTree[k].rightLink;
				break;
			}
			case '0':
			{
				k = hfTree[k].leftLink;
				break;
			}
		}
		if (k >= 0 && k < length)
		{
			output += hfTree[k].ch;
			k = root;
		}
	}
	return output;
}

void Huffman::encode(map<char, string> &code)
{
	//栈中元素为当前索引与编码
	stack<pair<int, string> > treeStack;
	//当前编码
	string tempCode;
	int i = root;
	if (i == 0)
	{
		code.emplace(hfTree[i].ch, "0");
		return;
	}
	while (i != -1 || !treeStack.empty())
	{
		while (i != -1)
		{
			treeStack.push(make_pair(i, tempCode));
			if (i >= 0 && i < length)
			{
				code.emplace(hfTree[i].ch, treeStack.top().second);
			}
			else
			{
				tempCode.push_back('0');
			}

			i = hfTree[i].leftLink;
		}
		i = treeStack.top().first;
		tempCode = treeStack.top().second;
		treeStack.pop();
		i = hfTree[i].rightLink;
		tempCode.push_back('1');
	}
}


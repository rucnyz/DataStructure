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
	hfTree = (HuffmanTree) malloc(m * sizeof(HtNode));
	// 为赫夫曼树分配一组顺序空间
	int i = 0;
	auto p = hfTree;
	auto w = weight.begin();
	for (; i < n; ++i, ++p, ++w)
	{
		*p = {(*w).second, 0, -1, -1, (*w).first};
	}
	// n个带权结点形成初始化的森林，每个结点的左、右孩子为空
	for (; i < m; ++i, ++p)
	{
		*p = {0, 0, 0, 0, '\0'};
	}
	// 对尚未使用的结点赋初值
	int s1, s2;
	for (i = n; i < m; ++i)
	{   // 建赫夫曼树
		Select(hfTree, i, s1, s2);
		// 在HT[1..i-1]当前可选的结点中选择parent为0，且权值
		// 最小的两个结点，其序号分别为s1和s2。
		hfTree[s1].parent = i;
		hfTree[s2].parent = i;
		hfTree[i].leftLink = s1;
		hfTree[i].rightLink = s2;
		hfTree[i].weight = hfTree[s1].weight + hfTree[s2].weight;
		// 取左、右子树根结点权值之和
	}
	hfTree[i - 1].parent = -1;
	root = i - 1;
}

Huffman::Huffman() : root(0), length(0), hfTree(nullptr)
{

}

void Huffman::Select(HuffmanTree tree, int i, int &s1, int &s2)
{
	float s1Weight = 1.0;
	float s2Weight = 1.1;
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

string Huffman::concat(const string &password, map<char, string> &code)
{
	string output;
	for (auto i = password.begin(); i < password.end(); ++i)
	{
		output += code.find(*i)->second;
	}
	return output;
}

string Huffman::decode(string &password)
{
	int k = root;
	string output;
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
	stack<pair<int, string> > treeStack;
	string binary;
	int i = root;
	while (i != -1 || !treeStack.empty())
	{
		while (i != -1)
		{
			treeStack.push(make_pair(i, binary));
			if (i >= 0 && i < length)
			{
				code.emplace(hfTree[i].ch, treeStack.top().second);
			}
			else
			{
				binary.push_back('0');
			}

			i = hfTree[i].leftLink;
		}
		i = treeStack.top().first;
		binary = treeStack.top().second;
		treeStack.pop();
		i = hfTree[i].rightLink;
		binary.push_back('1');
	}
}


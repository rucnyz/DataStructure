#include <iostream>
#include <algorithm>    // transform
#include "SqBiTree.h"
#include "LinkBiTree.h"
#include "Huffman.h"

float Weight[26] = {
		0.0856, 0.0139, 0.0297, 0.0378, 0.1304, 0.0289, 0.0199, 0.0528, 0.0627,
		0.0013, 0.0042, 0.0339, 0.0249, 0.0707, 0.0797, 0.0199, 0.0012, 0.0677,
		0.0607, 0.1045, 0.0249, 0.0092, 0.0149, 0.0017, 0.0199, 0.0008
};

int countAndGetWeight(const string &input, map<char, float> &weight)
{
	int count = 0;
	char num[26] = {0};
	string temp;
	temp.resize(input.size());
	//转换成小写
	transform(input.begin(), input.end(), temp.begin(), ::tolower);
	for (auto i = temp.begin(); i < temp.end(); i++)
	{
		if ((*i) >= 97 && (*i) <= 122)
		{
			num[(*i - 97)]++;
		}
	}
	int j = 0;
	for (char i : num)
	{
		if (i != 0)
		{
			count++;
			weight.emplace(j + 97, Weight[j]);
		}
		j++;
	}
	return count;
}

int main()
{
	int a;
	cout << "请选择输入二叉树或是哈夫曼编码" << endl;
	cin >> a;
	if (a == 1)
	{
		map<char, float> weight;
		map<char, string> code;
		string input("abcd"), output;
		cout << "请输入字符串" << endl;
		cin >> input;
		int length = countAndGetWeight(input, weight);
		Huffman hf(length, weight);
		hf.encode(code);
		string password = Huffman::concat(input, code);
		cout << password << endl;
		output = hf.decode(password);
		cout << output << endl;
	}
	else if (a == 2)
	{
		BiTree tree;
		cout << "请选择二叉树的输入方式(先序遍历输入1,广义表方式输入2)" << endl;
		int flag = 0;
		cin >> flag;
		if (flag == 1)
		{
			if (CreateBiTree(tree))
			{
				cout << "创建成功!" << endl;
			}
			else
			{
				cout << "创建失败" << endl;
			}
		}
		else if (flag == 2)
		{
			if (CreateBiTreeInList(tree))
			{
				cout << "创建成功!" << endl;
			}
			else
			{
				cout << "创建失败" << endl;
			}
		}
		cout << "树高:";
		cout << height(tree) << endl;
		cout << "================" << endl;
		cout << "叶节点数:";
		cout << countLeaves(tree) << endl;
		cout << "================" << endl;

		cout << "前序遍历:" << endl;
		PreOrderTraverse_recurse(tree, PrintElement);
		cout << endl;
		PreOrderTraverse_loop(tree, PrintElement);
		cout << endl;
		cout << "================" << endl;

		cout << "中序遍历:" << endl;
		InOrderTraverse_recurse(tree, PrintElement);
		cout << endl;
		InOrderTraverse_loop(tree, PrintElement);
		cout << endl;
		cout << "================" << endl;

		cout << "后序遍历:" << endl;
		PostOrderTraverse_recurse(tree, PrintElement);
		cout << endl;
		PostOrderTraverse_loop(tree, PrintElement);
		cout << endl;
		cout << "================" << endl;

		cout << "层次遍历:" << endl;
		LevelOrderTraverse(tree, PrintElement);
		cout << endl;
		cout << "================" << endl;
	}
	return 0;
}

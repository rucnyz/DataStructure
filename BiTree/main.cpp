#include <iostream>
#include <algorithm>    // transform
#include "SqBiTree.h"
#include "LinkBiTree.h"
#include "Huffman.h"

//float Weight[26] = {
//		0.0856, 0.0139, 0.0297, 0.0378, 0.1304, 0.0289, 0.0199, 0.0528, 0.0627,
//		0.0013, 0.0042, 0.0339, 0.0249, 0.0707, 0.0797, 0.0199, 0.0012, 0.0677,
//		0.0607, 0.1045, 0.0249, 0.0092, 0.0149, 0.0017, 0.0199, 0.0008
//};

/// 计算输入字符串不同字符的数量，并把各字符与权重对应起来
/// \param input 输入的字符串
/// \param weight 存储每个字符与对应的权重
/// \return 返回不同字符的数量
int countAndGetWeight(string &input, map<char, float> &weight)
{
	//制表
	int count = 0;
	char num[27] = {0};
	string temp;
	temp.resize(input.size());
	//转换成小写
	transform(input.begin(), input.end(), temp.begin(), ::tolower);
	input = temp;
	for (auto i = temp.begin(); i < temp.end(); i++)
	{
		if ((*i) >= 97 && (*i) <= 122)
		{
			num[(*i - 97)]++;
		}
		else
		{
			num[26]++;
		}
	}
	int j = 0;
	for (char i : num)
	{
		if (j == 26)
		{
			count++;
			weight.emplace(' ', (int) i);
		}
		else if (i != 0)
		{
			count++;
			weight.emplace(j + 97, (int) i);
		}
		j++;
	}
	return count;
}

int main()
{
	int a;
	cout << "请选择哈夫曼编码或者输入二叉树" << endl;
	cin >> a;
	getchar();
	if (a == 1)
	{
		map<char, float> weight;
		map<char, string> code;
		string input, password, output;

		cout << "请输入你的信息:" << endl;
		getline(cin, input);
		int length = countAndGetWeight(input, weight);

		Huffman hf(length, weight);
		hf.encode(code);

		password = Huffman::concat(input, code);
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

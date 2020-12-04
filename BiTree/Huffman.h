/*
 * -*- coding: utf-8 -*-
 * @Time    : 2020/12/4 8:33
 * @Author  : nieyuzhou
 * @File    : Huffman.h/cpp
 * @Software: CLion
 */
#ifndef BITREE_HUFFMAN_H
#define BITREE_HUFFMAN_H

#include <iostream>
#include <cmath>
#include <map>
#include <queue>
#include <stack>

using namespace std;

class Huffman
{
public:
	Huffman();

	/// 构造哈夫曼树
	/// \param n 外部节点个数
	/// \param weight 字符与权重对应表
	Huffman(int n, map<char, float> &weight);

	/// 将输入字符串转换为编码
	/// \param input 输入字符串
	/// \param code 字符与编码对应表
	/// \return 返回编码
	static string concat(const string &input, map<char, string> &code);

	/// 将编码转换为原字符串
	/// \param password 编码
	/// \return 返回原字符串
	string decode(string &password);

	/// 对字符进行编码
	/// \param code 得到的字符与编码对应表
	void encode(map<char, string> &code);

private:
	typedef struct // 哈夫曼树结点的结构
	{
		float weight;
		int parent, leftLink, rightLink;
		char ch;
	} HtNode, *HuffmanTree;
	HuffmanTree hfTree; // 哈夫曼树
	int root; // 哈夫曼树根在数组中的位置
	int length; // 外部节点个数

	/// 在HT[0..i-1]当前可选的结点中选择parent为0，权值最小的两个节点
	/// \param tree 哈夫曼树
	/// \param i 选择范围
	/// \param s1 存储最小节点之一
	/// \param s2 存储最小节点之一
	static void Select(HuffmanTree tree, int i, int &s1, int &s2);
};


#endif //BITREE_HUFFMAN_H

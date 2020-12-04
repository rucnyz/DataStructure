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

//typedef struct    /* 哈夫曼树结点的结构 */
//{
//	int ww;
//	int parent, llink, rlink;
//} HtNode, *HuffmanTree;
//
//
//struct HtTree
//{
//	HtNode ht[100]{};
//	int root = 0;    /* 哈夫曼树根在数组中的位置 */
//};
class Huffman
{
public:
	Huffman();

	explicit Huffman(int n, map<char, float> &weight);

	static string concat(const string &password, map<char, string> &code);

	string decode(string &password);

	void encode(map<char, string> &code);

private:
	typedef struct    /* 哈夫曼树结点的结构 */
	{
		float weight;
		int parent, leftLink, rightLink;
		char ch;
	} HtNode, *HuffmanTree;
	HuffmanTree hfTree;
	int root;    /* 哈夫曼树根在数组中的位置 */
	int length; //外部节点个数
	void Select(HuffmanTree tree, int i, int &s1, int &s2);
};


#endif //BITREE_HUFFMAN_H

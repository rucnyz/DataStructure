/*
 * -*- coding: utf-8 -*-
 * @Time    : 2020/11/23 18:18
 * @Author  : nieyuzhou
 * @File    : LinkBiTree.h/cpp
 * @Software: CLion
 */
#ifndef BITREE_LINKBITREE_H
#define BITREE_LINKBITREE_H

#include <cmath>
#include "SqBiTree.h"
#include <stack>
#include <queue>

typedef struct BiTNode
{
	TELemType data{};
	struct BiTNode *lchild{}, *rchild{};
} BiTNode, *BiTree;

bool CreateBiTreeInList(BiTree &T)
{
	string input;
	cout << "请输入广义表:" << endl;
	cin.clear();
	getline(cin, input);
	for (auto i = input.begin(); i < input.end(); ++i)
	{
		if (*i == ' ')
		{
			continue;
		}

	}
	return true;
}

bool CreateBiTree(BiTree &T)
{
	char ch;
	cout << "请输入值:";
	cin >> ch;
	if (ch == '#')
	{
		T = nullptr;
	}
	else
	{
		if (!(T = (BiTNode *) malloc(sizeof(BiTNode))))
		{
			exit(OVERFLOW);
		}
		T->data = ch;
		CreateBiTree(T->lchild);
		CreateBiTree(T->rchild);
	}
	return true;
}

bool PrintElement(TELemType e)
{
	cout << e;
	return true;
}

int height(BiTree &T, int count = 1)
{
	static int maxHeight = 0;
	if (T)
	{
		if (count > maxHeight)
		{
			maxHeight = count;
		}
		if (T->lchild)
		{
			height(T->lchild, ++count);
			count--;
		}
		if (T->rchild)
		{
			height(T->rchild, ++count);
			count--;
		}
	}
	return maxHeight;
}

int countLeaves(BiTree &T)
{
	static int count = 0;
	if ((!T->rchild) && (!T->lchild))
	{
		count++;
		return count;
	}
	if (T->lchild)
	{
		countLeaves(T->lchild);
	}
	if (T->rchild)
	{
		countLeaves(T->rchild);
	}
	return count;
}

bool PreOrderTraverse_recurse(BiTree &T, bool(*Visit)(TELemType e))
{
	if (T)
	{
		if (Visit(T->data))
		{
			if (PreOrderTraverse_recurse(T->lchild, Visit))
			{
				if (PreOrderTraverse_recurse(T->rchild, Visit))
				{
					return true;
				}
			}
		}
		return false;
	}
	return true;
}

bool PreOrderTraverse_loop(BiTree T, bool(*Visit)(TELemType e))
{
	stack <BiTree> treeStack;
	if (!T)
	{
		printf("空树！\n");
		return false;
	}
	while (T || !treeStack.empty())
	{
		while (T)
		{
			treeStack.push(T);
			Visit(T->data);
			T = T->lchild;
		}
		T = treeStack.top();
		treeStack.pop();
		T = T->rchild;
	}
	return true;
}

bool InOrderTraverse_recurse(BiTree &T, bool(*Visit)(TELemType e))
{
	if (T)
	{
		if (InOrderTraverse_recurse(T->lchild, Visit))
		{
			if (Visit(T->data))
			{
				if (InOrderTraverse_recurse(T->rchild, Visit))
				{
					return true;
				}
			}
		}
		return false;
	}
	return true;
}

bool InOrderTraverse_loop(BiTree T, bool(*Visit)(TELemType e))
{
	stack <BiTree> treeStack;
	if (!T)
	{
		printf("空树！\n");
		return false;
	}

	while (T || !treeStack.empty())
	{
		while (T)
		{
			treeStack.push(T);
			T = T->lchild;
		}
		T = treeStack.top();
		treeStack.pop();
		Visit(T->data);
		T = T->rchild;
	}
	return true;
}

bool PostOrderTraverse_loop(BiTree T, bool(*Visit)(TELemType e))
{
	int flag[20];
	stack <BiTree> treeStack;
	if (!T)
	{
		printf("空树！\n");
		return false;
	}
	while (T)
	{
		treeStack.push(T);
		flag[treeStack.size()] = 0;
		T = T->lchild;
	}
	while (!treeStack.empty())
	{
		T = treeStack.top();
		while (T && T->rchild && flag[treeStack.size()] == 0)
		{
			flag[treeStack.size()] = 1;
			T = T->rchild;
			while (T)
			{
				treeStack.push(T);
				flag[treeStack.size()] = 0;
				T = T->lchild;
			}
		}
		T = treeStack.top();
		Visit(T->data);
		treeStack.pop();
	}
	return true;
}

bool PostOrderTraverse_recurse(BiTree &T, bool(*Visit)(TELemType e))
{
	if (T)
	{
		if (PostOrderTraverse_recurse(T->lchild, Visit))
		{
			if (PostOrderTraverse_recurse(T->rchild, Visit))
			{
				if (Visit(T->data))
				{
					return true;
				}
			}
		}
		return false;
	}
	return true;
}

bool LevelOrderTraverse(BiTree T, bool(*Visit)(TELemType e))
{
	queue<char> data;
	while (T)
	{
		Visit(T->data);
		if (T->lchild)
		{
			T = T->lchild;
			data.push(T->data);
		}
		if (T->rchild)
		{
			T = T->rchild;
			data.push(T->data);
		}
	}
	return true;
}

#endif //BITREE_LINKBITREE_H

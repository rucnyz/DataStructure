#include <iostream>
#include "SqBiTree.h"
#include "LinkBiTree.h"

int main()
{
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

#include <iostream>
#include "SqBiTree.h"
#include "LinkBiTree.h"

int main()
{
	{
		BiTree tree;
		if (CreateBiTree(tree))
		{
			cout << "创建成功!" << endl;
		}
		else
		{
			cout << "创建失败" << endl;
		}
		cout << "树高:";
		cout << height(tree) << endl;
		cout << "================" << endl;
		cout << "叶节点数:";
		cout << countLeaves(tree) << endl;
		cout << "================" << endl;
		cout << "前序遍历:" << endl;
		PreOrderTraverse_reverse(tree, PrintElement);
		cout << "================" << endl;
		cout << "中序遍历:" << endl;
		InOrderTraverse_reverse(tree, PrintElement);
		cout << "================" << endl;
		cout << "后序遍历:" << endl;
		PostOrderTraverse_reverse(tree, PrintElement);
		cout << "================" << endl;
		cout << "层次遍历:" << endl;
		LevelOrderTraverse(tree, PrintElement);
		cout << "================" << endl;
	}
	return 0;
}

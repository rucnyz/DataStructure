#include <iostream>
#include "ALGraph.h"

int main()
{
	bool flag = true;
	ALGraph graph;
	string input = R"(C:\Users\nieyuzhou\CLionProjects\DataStructure\Flight_Scheduling\flight_data.csv)";
	HandleOriginData(input, graph);// flight[2500]
	graph.Create();
	graph.Floyd();
//  搜索不在系统之中
//	cout << "是否进行优先搜索？" << endl;
//	int s = 0;
//	cin >> s;
//	if (s == 1)
//	{
//		cout << "广度优先搜索:" << endl;
//		graph.BFS(56);
//		cout << "深度优先搜索:" << endl;
//		graph.DFS(23);
//	}
	cout << "欢迎使用航班查询系统v1.0!" << endl;
	while (flag)
	{
		int start, end;
		string id;
		cout << "请输入您想要查询的两个机场编号：" << endl;
		cin >> start >> end;
		if (start > 79 || start <= 0 || end > 79 || end <= 0)
		{
			cout << "机场不存在! 机场编号在1-79之间" << endl;
			continue;
		}
		bool isError = true;
		while (isError)
		{
			cout << "请选择您想要进行的操作：" << endl;
			cout << "    输入1查询两个机场之间的中转次数" << endl;
			cout << "    输入2查询两个机场之间的最短飞行时间" << endl;
			cout << "    输入3查询两个机场之间的所有可能航线(仅限直飞或两次中转以内)" << endl;
			cout << "    输入4进行条件查询" << endl;
			cout << "    输入0退出系统" << endl;
			cin >> id;
			int idx;
			try
			{
				idx = stoi(id);
			}
			catch (std::invalid_argument &argument)
			{
				cout << "您的输入不合法! 请输入整数" << endl;
				continue;
			}
			switch (idx)
			{
				case 1:
				case 2:
				case 3:
				case 4:
				{
					graph.mainFunc(start, end, idx);
					isError = false;
					break;
				}
				case 0:
				{
					flag = false;
					isError = false;
					break;
				}
				default:
				{
					cout << "您的输入不合法! 请重新输入" << endl;
				}
			}
		}
	}
	cout << " 感谢您的使用！" << endl;
	return 0;
}
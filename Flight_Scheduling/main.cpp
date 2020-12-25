#include <iostream>
#include "ALGraph.h"

int main()
{
	bool flag = true;
	ALGraph graph;
	string input = R"(C:\Users\nieyuzhou\CLionProjects\DataStructure\Flight_Scheduling\flight_data.csv)";
	HandleOriginData(input, graph);// flight[2500]
	graph.Create();
//	graph.DFS(1, 49, 2);
	cout << "是否进行广度优先搜索？" << endl;
	int s = 0;
	cin >> s;
	if (s == 1)
	{
		cout << "广度优先搜索:" << endl;
		graph.BFS(1);
	}
	cout << "欢迎使用航班查询系统v1.0!" << endl;
	while (flag)
	{
		int start, end;
		string id;
		cout << "请输入您想要查询的两个机场编号：" << endl;
		cin >> start >> end;
		cout << "请选择您想要进行的操作：" << endl;
		cout << "    输入1查询两个机场之间的最短飞行时间" << endl;
		cout << "    输入2查询两个机场之间的所有可能航线(仅限直飞或两次中转以内)" << endl;
		cout << "    输入3进行条件查询" << endl;
		cout << "    输入quit退出系统" << endl;
		cin >> id;
		switch (id[0])
		{
			case '1':
			{
				graph.DFS(start, end, 1);
				break;
			}
			case '2':
			{
				graph.DFS(start, end, 2);
				break;
			}
			case '3':
			{
				graph.DFS(start, end, 3);
				break;
			}
			case 'q':
			{
				flag = false;
				break;
			}
		}
	}
	cout << " 感谢您的使用！" << endl;
	return 0;
}
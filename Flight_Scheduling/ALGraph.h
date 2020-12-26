/*
 * -*- coding: utf-8 -*-
 * @Time    : 2020/12/14 16:56
 * @Author  : nieyuzhou
 * @File    : ALGraph.h
 * @Software: CLion
 */
#ifndef FLIGHT_SCHEDULING_GRAPH_H
#define FLIGHT_SCHEDULING_GRAPH_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <list>
#include <queue>
#include <stack>
#include <cstring>

using namespace std;
//存储所有航班信息，共2346条，从1开始
typedef struct Flight
{
	static int totalFlightNum;
	bool intlOrDome{};// 暂未使用
	int flightId{};// 暂未使用
	int flightNo{};
	int departureAirport{};
	int arrivalAirport{};
	int airplaneId{};
	int airplaneModel{};
	int airFares{};
	string departureTime{};
	string arrivalTime{};
	string departureDate{}; // 暂未使用
} Flight_Arr[2350];

// 存储边(航班)
typedef struct ArcNode
{
	int adjVex{};   // 该弧所指向的顶点的位置，也就是机场在数组中的位置
	struct ArcNode *nextArc{};   // 指向下一条弧的指针
	int flightID[34]{};   // 所有连接这两点的弧对应的航班编号，因为同一航线可能有多个航班
	int num{};   // 这条航线有多少航班
} ArcNode;
// 存储顶点(机场)
typedef struct VNode
{
	ArcNode *firstArc;
} AdjList[80];   //一共79个机场

// 存储每两个机场之间的航班(用于进行条件搜索)
struct MultiArcNode
{
	int startVex{};
	int targetVex{};
	list<pair<int, list<int> > > pathVex{};
};

//主要使用的图类
class ALGraph
{
public:
	AdjList vertices{}; //所有顶点
	int edge[80][80]{}; //邻接矩阵
	int vexNum = 0, arcNum = 0; //图的当前顶点数和弧数

	void Create();

	/// 用于分发操作
	/// \param departure 出发机场
	/// \param arrival 目的机场
	/// \param opId 对应不同功能
	void mainFunc(int departure, int arrival, int opId);

	// 广搜
	void BFS(int v);

	// 深搜
	void DFS(int v);

	// 进行数据处理
	friend void HandleOriginData(const string &path, ALGraph &graph);

	// 分割字符串
	friend vector<string> split(const string &str, const string &delim);

	// 使用邻接矩阵计算连通性,O(n3)
	void floyd();

private:
	Flight_Arr flight; //所有航班

	// 用于比较时间 后一时间晚于前一时间返回true
	static bool compareTime(const string &prior, const string &next);

	// 求时间差，时间差字符串为每两位断开，从左往右代表日、小时、分钟
	static string timeDifference(const string &prior, const string &next);

	// 用于找到两个机场之间的所有可行路径,存在output中并输出
	void findAllPathForOutput(int departure, int arrival, ArcNode *p, string &priorArrivalTime, bool *visited,
	                          vector<string> &output);

	// (已废除)递归形式的深搜，用于创建邻接矩阵
	void DFS_recurse(int departure, int arrival, ArcNode *p, string &priorArrivalTime, bool *visited,
	                 vector<string> &output);

	// 用于输出结果
	static inline void Display(vector<string> &output)
	{
		if (output.empty())
		{
			cout << "无符合条件的航班！" << endl;
		}
		for (auto i = output.begin(); i < output.end(); ++i)
		{
			cout << *i << endl;
		}
		cout << "======================" << endl;
	}

	// (已废除)创建邻接矩阵
	void CreateMatrix(vector<string> &output);

	// 用于找到两个机场之间的所有可行路径,并从中找到时间最短的路径
	void findLeastTime(int departure, int arrival, ArcNode *p, string &priorArrivalTime, bool *visited,
	                   vector<string> &output, string &time, string &startTime);

	// 用于对已找到的所有可行路线进行条件搜索
	void findPathInCondition(string &model, string &departureTime1, string &departureTime2, string &arrivalTime1,
	                         string &arrivalTime2, string &transferTime, list<MultiArcNode> &path);

	// 用于找到两个机场之间所有可行路线，存入allPath中以备条件搜索
	void findAllPathForConditionSearch(int departure, int arrival, ArcNode *p, string &priorArrivalTime, bool *visited,
	                                   vector<string> &eachPath, list<MultiArcNode> &allPath);

};


#endif //FLIGHT_SCHEDULING_GRAPH_H

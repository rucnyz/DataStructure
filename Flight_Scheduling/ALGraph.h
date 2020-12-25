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
typedef struct Flight
{
	static int totalFlightNum;
	bool intlOrDome{};
	int flightId{};
	int flightNo{};
	int departureAirport{};
	int arrivalAirport{};
	int airplaneId{};
	int airplaneModel{};
	int airFares{};
	string departureTime{};
	string arrivalTime{};
	string departureDate{};
} Flight_Arr[2350];   //从1开始
typedef struct ArcNode
{
	int adjVex{};   //该弧所指向的顶点的位置，也就是机场在数组中的位置
	struct ArcNode *nextArc{};   //指向下一条弧的指针
	int flightID[34]{};   //所有连接这两点的弧对应的航班编号，因为同一航线可能有多个航班
	int num{};   //这条航线有多少航班
} ArcNode;
typedef struct VNode
{
	ArcNode *firstArc;
} AdjList[80];   //一共79个机场


struct MultiArcNode
{
	int startVex{};
	int targetVex{};
	list<pair<int, list<int> > > pathVex{};
};

class ALGraph
{
public:
	void Create();

	void DFS(int departure, int arrival, int opId);

	void BFS(int v);

	friend void HandleOriginData(const string &path, ALGraph &graph);

	friend vector<string> split(const string &str, const string &delim);

	AdjList vertices{}; //所有顶点
	int edge[80][80]{}; //邻接矩阵
	int vexNum = 0, arcNum = 0; //图的当前顶点数和弧数

private:
	Flight_Arr flight;

	///
	/// \param prior
	/// \param next
	/// \return 后一时间晚于前一时间
	static bool compareTime(const string &prior, const string &next);

	/// 求时间差
	/// \param prior
	/// \param next
	/// \return 时间差字符串
	static string timeDifference(const string &prior, const string &next);

	void findAllPath(int departure, int arrival, ArcNode *p, string &priorArrivalTime, bool *visited,
	                 vector<string> &output);

	void DFS_recurse(int departure, int arrival, ArcNode *p, string &priorArrivalTime, bool *visited,
	                 vector<string> &output);

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

	void CreateMatrix(vector<string> &output);

	///
	/// \param departure
	/// \param arrival
	/// \param p
	/// \param priorArrivalTime
	/// \param visited
	/// \param output
	/// \param time 每两位断开，从左往右代表日、小时、分钟
	void findLeastCost(int departure, int arrival, ArcNode *p, string &priorArrivalTime, bool *visited,
	                   vector<string> &output, string &time, string &startTime);

	void findPathInCondition(string &model, string &departureTime1, string &departureTime2, string &arrivalTime1,
	                         string &arrivalTime2, string &transferTime, list<MultiArcNode> &path);

	void findAllPath2(int departure, int arrival, ArcNode *p, string &priorArrivalTime, bool *visited,
	                  vector<string> &eachPath, list<MultiArcNode> &allPath);
};


#endif //FLIGHT_SCHEDULING_GRAPH_H

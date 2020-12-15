/*
 * -*- coding: utf-8 -*-
 * @Time    : 2020/12/14 16:56
 * @Author  : nieyuzhou
 * @File    : ALGraph.h
 * @Software: CLion
 */
#ifndef FLIGHT_SCHEDULING_GRAPH_H
#define FLIGHT_SCHEDULING_GRAPH_H

#include "DataLoader.h"

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
class ALGraph
{
public:
	explicit ALGraph();

	void DFS(int v);

	AdjList vertices{};   //所有顶点
	int vexNum = 0, arcNum = 0;   //图的当前顶点数和弧数
private:
	static bool compareTime(const string &prior, const string &next);

};


#endif //FLIGHT_SCHEDULING_GRAPH_H

/*
 * -*- coding: utf-8 -*-
 * @Time    : 2020/12/14 16:56
 * @Author  : nieyuzhou
 * @File    : Graph.cpp
 * @Software: CLion
 */
#include "ALGraph.h"

Flight flight[2350];

ALGraph::ALGraph()
{
	this->arcNum = Flight::totalFlightNum;
	this->vexNum = 79;
	for (int i = 1; i <= this->vexNum; i++)
	{   //初始化顶点信息
		this->vertices[i].firstArc = nullptr;
	}
	//用航班信息建立邻接表
	for (int id = 1; id <= this->arcNum; id++)
	{
		int i, j;
		i = flight[id].departureAirport;
		j = flight[id].arrivalAirport;
		ArcNode *p = this->vertices[i].firstArc;
		while (p)
		{
			//不是第一次出现这条航线
			if (p->adjVex == j)
			{
				p->flightID[++p->num] = id;
				break;
			}
			p = p->nextArc;
		}
		//遍历结束发现这条航线未出现过
		if (p == nullptr)
		{
			ArcNode *q;
			q = (ArcNode *) malloc(sizeof(ArcNode));
			q->num = 0;
			q->flightID[0] = id;
			//存储目的地
			q->adjVex = j;
			//头插法插入边结点
			q->nextArc = this->vertices[i].firstArc;
			this->vertices[i].firstArc = q;
		}
	}
}

void ALGraph::DFS(int v)
{
	stack<pair<int, string> > S;
	S.push(make_pair(v, ""));
	bool visited[80] = {false};
	while (!S.empty())
	{
		int t = S.top().first;
		string priorArrivalTime = S.top().second;
		S.pop();
		ArcNode *p = this->vertices[t].firstArc;
		while (p)
		{
			if (visited[p->adjVex])
			{
				p = p->nextArc;
				continue;
			}
			//找到最早到达且时间在上一航班之后的航班
			string minArrivalTime;
			for (int i = 0; i < p->num; ++i)
			{
				if (compareTime(priorArrivalTime, flight[p->flightID[i]].departureTime) &&
				    compareTime(flight[p->flightID[i]].arrivalTime, minArrivalTime)) // 离开时间晚于上一个到达时间
				{
					minArrivalTime = flight[p->flightID[i]].arrivalTime;
				}
			}
			S.push(make_pair(p->adjVex, minArrivalTime));
			visited[p->adjVex] = true;
			p = p->nextArc;
		}
	}
}

///
/// \param prior
/// \param next
/// \return 后一时间晚于前一时间
bool ALGraph::compareTime(const string &prior, const string &next)
{
	if (prior.empty() || next.empty())
	{
		return true;
	}
	else
	{
		return prior < next;
	}
}

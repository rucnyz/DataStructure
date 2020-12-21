/*
 * -*- coding: utf-8 -*-
 * @Time    : 2020/12/14 16:56
 * @Author  : nieyuzhou
 * @File    : Graph.cpp
 * @Software: CLion
 */
#include "ALGraph.h"


void ALGraph::Create()
{
	arcNum = Flight::totalFlightNum;
	vexNum = 79;
	for (int i = 1; i <= this->vexNum; i++)
	{   //初始化顶点信息
		vertices[i].firstArc = nullptr;
	}
	//用航班信息建立邻接表
	for (int id = 1; id <= arcNum; id++)
	{
		int i, j;
		i = flight[id].departureAirport;
		j = flight[id].arrivalAirport;
		//邻接表
		ArcNode *p = vertices[i].firstArc;
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
			p = (ArcNode *) malloc(sizeof(ArcNode));
			p->num = 0;
			p->flightID[0] = id;
			//存储目的地
			p->adjVex = j;
			//头插法插入边结点
			p->nextArc = vertices[i].firstArc;
			vertices[i].firstArc = p;
		}
		//邻接矩阵
	}
}

void ALGraph::BFS(int v)
{
	queue<pair<int, string> > S;
	string chain;
	S.push(make_pair(v, ""));
	bool visited[80] = {false};
	while (!S.empty())
	{
		int t = S.front().first;
		string priorArrivalTime = S.front().second;
		S.pop();
		ArcNode *p = vertices[t].firstArc;
		while (p)
		{
			if (visited[p->adjVex])
			{
				p = p->nextArc;
				continue;
			}
			//找到最早到达且时间在上一航班之后的航班
			string minArrivalTime;
			for (int i = 0; i <= p->num; ++i)
			{
				if (compareTime(priorArrivalTime, flight[p->flightID[i]].departureTime) &&
				    compareTime(flight[p->flightID[i]].arrivalTime, minArrivalTime)) // 离开时间晚于上一个到达时间
				{
					minArrivalTime = flight[p->flightID[i]].arrivalTime;
				}
			}
			S.push(make_pair(p->adjVex, minArrivalTime));
			visited[p->adjVex] = true;
			if (!minArrivalTime.empty())
			{
				static int count = 0;
				count++;
				cout << p->adjVex << " " << minArrivalTime << " " << count << endl;
			}
			p = p->nextArc;
		}
	}
}

void ALGraph::DFS(int departure, int arrival, int opId)
{

	bool visited[80] = {false};
	string priorArrivalTime;
	ArcNode *p = vertices[departure].firstArc;
	vector<string> output;
	visited[departure] = true;
	if (opId == 1)
	{
		static string leastTime = "999999";
		string a;
		for (int i = 0; i <= p->num; ++i)
		{
			if (compareTime(flight[p->flightID[i]].departureTime, a))
			{
				a = flight[p->flightID[i]].departureTime;
			}

		}
		findLeastCost(departure, arrival, p, priorArrivalTime, visited, output, leastTime,
		              a);
		cout << leastTime << endl;
	}
	else
	{
		findAllPath(departure, arrival, p, priorArrivalTime, visited, output);
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
		if (prior.size() != next.size() && prior[2] == next[2])
		{
			return (next.size() > prior.size());
		}
		else
		{
			return prior < next;
		}
	}
}

void ALGraph::findAllPath(int departure, int arrival, ArcNode *p, string &priorArrivalTime, bool *visited,
                          vector<string> &output)
{
//	if (output.size() > 10)
//	{
//		return;
//	}
	while (p)
	{
		if (visited[p->adjVex])
		{
			p = p->nextArc;
			continue;
		}
		//找到最早到达且时间在上一航班之后的航班
		string minArrivalTime;
		for (int i = 0; i <= p->num; ++i)
		{
			// 离开时间晚于上一个到达时间
			if (compareTime(priorArrivalTime, flight[p->flightID[i]].departureTime) &&
			    compareTime(flight[p->flightID[i]].arrivalTime, minArrivalTime))
			{
				minArrivalTime = flight[p->flightID[i]].arrivalTime;
			}
		}
		//找到了航班
		if (!minArrivalTime.empty())
		{
			visited[p->adjVex] = true;
			stringstream os;
			string temp;
			os << departure << "->" << p->adjVex << "航班号:";
			for (int i = 0; i < p->num; ++i)
			{
				os << p->flightID[i] << ",";
			}
			os << p->flightID[p->num];
			os >> temp;
			output.push_back(temp);
			if (p->adjVex == arrival)
			{
				Display(output);
			}
			else
			{
				findAllPath(p->adjVex, arrival, vertices[p->adjVex].firstArc, minArrivalTime, visited, output);
			}
			visited[p->adjVex] = false;
			output.pop_back();
		}
		p = p->nextArc;
	}
}

void ALGraph::findLeastCost(int departure, int arrival, ArcNode *p, string &priorArrivalTime, bool *visited,
                            vector<string> &output, string &time, string &startTime)
{
	if (output.size()>4)
	{
		return;
	}
	while (p)
	{
		if (visited[p->adjVex])
		{
			p = p->nextArc;
			continue;
		}
		//找到最早到达且时间在上一航班之后的航班
		string minArrivalTime;
		for (int i = 0; i <= p->num; ++i)
		{
			// 离开时间晚于上一个到达时间
			if (compareTime(priorArrivalTime, flight[p->flightID[i]].departureTime) &&
			    compareTime(flight[p->flightID[i]].arrivalTime, minArrivalTime))
			{
				minArrivalTime = flight[p->flightID[i]].arrivalTime;
			}
		}
		//找到了航班
		if (!minArrivalTime.empty())
		{
			//时间长于已找到的,后面的不再遍历
			if (time != "999999" && time < timeDifference(startTime, minArrivalTime))
			{
				p = p->nextArc;
				continue;
			}
			visited[p->adjVex] = true;
			stringstream os;
			string temp;
			os << departure << "->" << p->adjVex << "航班号:";
			for (int i = 0; i < p->num; ++i)
			{
				os << p->flightID[i] << ",";
			}
			os << p->flightID[p->num];
			os >> temp;
			output.push_back(temp);
			if (p->adjVex == arrival)
			{
				string tmp = timeDifference(startTime, minArrivalTime);
				if (time > tmp)
				{
					time = tmp;
				}
			}
			else
			{
				findLeastCost(p->adjVex, arrival, vertices[p->adjVex].firstArc, minArrivalTime, visited, output, time,
				              startTime);
			}
			visited[p->adjVex] = false;
			output.pop_back();
		}
		p = p->nextArc;
	}
}

void ALGraph::DFS_recurse(int departure, int arrival, ArcNode *p, string &priorArrivalTime, bool *visited,
                          vector<string> &output)
{
	while (p)
	{
		if (visited[p->adjVex])
		{
			p = p->nextArc;
			continue;
		}
		//找到最早到达且时间在上一航班之后的航班
		string minArrivalTime;
		for (int i = 0; i <= p->num; ++i)
		{
			// 离开时间晚于上一个到达时间
			if (compareTime(priorArrivalTime, flight[p->flightID[i]].departureTime) &&
			    compareTime(flight[p->flightID[i]].arrivalTime, minArrivalTime))
			{
				minArrivalTime = flight[p->flightID[i]].arrivalTime;
			}
		}
		//找到了航班
		if (!minArrivalTime.empty())
		{
			visited[p->adjVex] = true;
			stringstream os;
			string temp;
			os << departure << "->" << p->adjVex;
			os >> temp;
			output.push_back(temp);
			DFS_recurse(p->adjVex, arrival, vertices[p->adjVex].firstArc, minArrivalTime, visited, output);
			visited[p->adjVex] = false;
			output.pop_back();
		}
		p = p->nextArc;
	}
	if (!output.empty())
	{
		Display(output);
	}
}

void ALGraph::BFS_recurse(int v, ArcNode *p, string &priorArrivalTime, bool *visited, vector<string> &output)
{

}

void ALGraph::CreateMatrix(vector<string> &output)
{
	int start = stoi(output.front());
	int target = stoi(output.back().substr(output.back().find('>') + 1));

	edge[start][target].startVex = start;
	edge[start][target].targetVex = target;
	edge[start][target].times = output.size();
	if (output.size() == 2)
	{
		edge[start][target].pathVex = stoi(output[1]);
	}

}

string ALGraph::timeDifference(const string &prior, const string &next)
{
	string result;
	int hour1 = stoi(prior.substr(9));
	int hour2 = stoi(next.substr(9));
	int minute1 = stoi(prior.substr(1 + prior.find(':')));
	int minute2 = stoi(next.substr(1 + next.find(':')));

	string tmp;
	tmp = prior;
	tmp[2] = next[2];
	//日期
	result += "0";
	if (prior[2] == next[2] || compareTime(tmp, next))
	{
		result += to_string(next[2] - prior[2]);
		int hourDiff = hour2 - hour1 - (minute1 > minute2);
		if (hourDiff < 10)
		{
			result += "0";
		}
		result += to_string(hourDiff);
		int minuteDiff = (60 + (minute2 - minute1)) % 60;
		if (minuteDiff < 10)
		{
			result += "0";
		}
		result += to_string(minuteDiff);
	}
	else
	{
		result += to_string(next[2] - prior[2] - 1);
		int hourDiff = 24 - hour1 + hour2 - (minute1 != 0) + (minute2 >= minute1);
		int minuteDiff = (60 - minute1 + minute2) % 60;
		if (hourDiff < 10)
		{
			result += "0";
		}
		result += to_string(hourDiff);
		if (minuteDiff < 10)
		{
			result += "0";
		}
		result += to_string(minuteDiff);
	}

	return result;
}

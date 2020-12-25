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

		a = flight[p->flightID[0]].departureTime;
		findLeastCost(departure, arrival, p, priorArrivalTime, visited, output, leastTime,
		              a);
		cout << leastTime << endl;
		leastTime = "999999";
	}
	else if (opId == 2)
	{
		findAllPath(departure, arrival, p, priorArrivalTime, visited, output);
	}
	else
	{
		string model, departureTime1, departureTime2, arrivalTime1, arrivalTime2, transferTime;
		cout << "请输入您想要添加的限制条件(如果无需限制请输入no):" << endl;
		cout << "airplane model:(e.g:1)";
		getchar();
		getline(cin, model);
		cout << "departure time(e.g:5/5/2017 16:55):" << endl;
		cout << "最早时间:";
		getline(cin, departureTime1);
		cout << "最晚时间:";
		getline(cin, departureTime2);
		cout << "arrival time(e.g:5/5/2017 16:55):" << endl;
		cout << "最早时间:";
		getline(cin, arrivalTime1);
		cout << "最晚时间:";
		getline(cin, arrivalTime2);
		cout << "transfer time(e.g:010101,前两位表示天，中间两位表示时，后两位表示分钟):" << endl;
		cout << "最大时间:";
		getline(cin, transferTime);
		static list<MultiArcNode> path;
		findAllPath2(departure, arrival, p, priorArrivalTime, visited, output, path);
		findPathInCondition(model, departureTime1, departureTime2, arrivalTime1, arrivalTime2, transferTime, path);
	}
}

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
	if (output.size() > 1)
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
	static int j = 1;
	if (output.size() > 4)
	{
		return;
	}
	while (p)
	{
		if (visited[p->adjVex])
		{
			if (output.empty() && (j != p->num + 1))
			{
				startTime = flight[p->flightID[j]].departureTime;
				j++;
			}
			else if (output.empty() && (j == p->num + 1))
			{
				p = p->nextArc;
				if (p)
				{
					startTime = flight[p->flightID[0]].departureTime;
				}
				j = 1;
			}
			else
			{
				p = p->nextArc;
			}
			continue;
		}
		//找到最早到达且时间在上一航班之后的航班
		string minArrivalTime;
		if (output.empty())
		{
			minArrivalTime = flight[p->flightID[j - 1]].arrivalTime;
		}
		else
		{
			for (int i = 0; i <= p->num; ++i)
			{
				// 离开时间晚于上一个到达时间
				if (compareTime(priorArrivalTime, flight[p->flightID[i]].departureTime) &&
				    compareTime(flight[p->flightID[i]].arrivalTime, minArrivalTime))
				{
					minArrivalTime = flight[p->flightID[i]].arrivalTime;
				}
			}
		}
		//找到了航班
		if (!minArrivalTime.empty())
		{
			//时间长于已找到的,后面的不再遍历
			if (time != "999999" && time < timeDifference(startTime, minArrivalTime))
			{
				if (output.empty() && (j != p->num + 1))
				{
					startTime = flight[p->flightID[j]].departureTime;
					j++;
				}
				else if (output.empty() && (j == p->num + 1))
				{
					p = p->nextArc;
					if (p)
					{
						startTime = flight[p->flightID[0]].departureTime;
					}
					j = 1;
				}
				else
				{
					p = p->nextArc;
				}
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
		if (output.empty() && (j != p->num + 1))
		{
			startTime = flight[p->flightID[j]].departureTime;
			j++;
		}
		else if (output.empty() && (j == p->num + 1))
		{
			p = p->nextArc;
			if (p)
			{
				startTime = flight[p->flightID[0]].departureTime;
			}
			j = 1;
		}
		else
		{
			p = p->nextArc;
		}
	}
}

vector<string> split(const string &str, const string &delim)
{
	vector<string> res;
	if (str.empty())
	{
		return res;
	}
	//先将要切割的字符串从string类型转换为char*类型
	char *c_str = new char[str.length() + 1]; //不要忘了
	strcpy(c_str, str.c_str());

	char *d = new char[delim.length() + 1];
	strcpy(d, delim.c_str());

	char *p = strtok(c_str, d);
	while (p)
	{
		string s = p; //分割得到的字符串转换为string类型
		res.push_back(s); //存入结果数组
		p = strtok(nullptr, d);
	}

	return res;
}

void ALGraph::findPathInCondition(string &model, string &departureTime1, string &departureTime2, string &arrivalTime1,
                                  string &arrivalTime2, string &transferTime, list<MultiArcNode> &path)
{
	vector<string> output;
	for (auto &i : path)
	{
		//判断起飞时段
		if (departureTime1 != "no" && departureTime2 != "no")
		{
			auto j = i.pathVex.front().second.begin();
			while (j != i.pathVex.front().second.end())
			{
				if (!compareTime(departureTime1, flight[*j].departureTime) ||
				    !compareTime(flight[*j].departureTime, departureTime2))
				{
					j = i.pathVex.front().second.erase(j);
				}
				else
				{
					j++;
				}
			}
		}
		//判断飞机模型
		if (model != "no")
		{
			for (auto &j : i.pathVex)
			{
				auto k = j.second.begin();
				while (k != j.second.end())
				{
					if (flight[*k].airplaneModel != stoi(model))
					{
						k = j.second.erase(k);
					}
					else
					{
						++k;
					}
				}
			}
		}
		//判断到达时段
		if (arrivalTime1 != "no" && arrivalTime2 != "no")
		{
			auto j = i.pathVex.back().second.begin();
			while (j != i.pathVex.back().second.end())
			{
				if (compareTime(flight[*j].arrivalTime, arrivalTime1) ||
				    compareTime(arrivalTime2, flight[*j].arrivalTime))
				{
					j = i.pathVex.back().second.erase(j);
				}
				else
				{
					j++;
				}
			}
		}
		for (auto j = i.pathVex.front().second.begin(); j != i.pathVex.front().second.end(); ++j)
		{
			for (auto k = i.pathVex.back().second.begin(); k != i.pathVex.back().second.end(); ++k)
			{
				if (compareTime(flight[*j].arrivalTime, flight[*k].departureTime))
				{
					//判断飞行时间
					if (transferTime == "no" ||
					    transferTime > timeDifference(flight[*j].departureTime, flight[*k].arrivalTime))
					{
						stringstream os;
						string temp;
						os << i.startVex << "->" << i.pathVex.begin()->first << "->" << i.targetVex;
						os >> temp;
						output.push_back(temp);
						temp.clear();
						os.clear();
						os << *j << "->" << *k;
						os >> temp;
						output.push_back(temp);
					}

				}
			}
		}
	}
	Display(output);
	path.clear();
}

void ALGraph::findAllPath2(int departure, int arrival, ArcNode *p, string &priorArrivalTime, bool *visited,
                           vector<string> &eachPath,
                           list<MultiArcNode> &allPath)
{
	if (eachPath.size() > 1)
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
			visited[p->adjVex] = true;
			stringstream os;
			string temp;
			os << departure << "," << p->adjVex << ",";
			for (int i = 0; i < p->num; ++i)
			{
				os << p->flightID[i] << ",";
			}
			os << p->flightID[p->num];
			os >> temp;
			eachPath.push_back(temp);
			if (p->adjVex == arrival)
			{
				MultiArcNode tmp;
				tmp.startVex = stoi(eachPath[0]);
				for (auto i = eachPath.begin(); i < eachPath.end(); ++i)
				{
					vector<string> a = split(*i, ",");
					list<int> x;
					for (auto j = a.begin() + 2; j < a.end(); ++j)
					{
						x.push_back(stoi(*j));
					}
					tmp.pathVex.emplace_back(stoi(a[1]), x);
				}
				tmp.targetVex = tmp.pathVex.back().first;
				allPath.push_back(tmp);
			}
			else
			{
				findAllPath2(p->adjVex, arrival, vertices[p->adjVex].firstArc, minArrivalTime, visited, eachPath,
				             allPath);
			}
			visited[p->adjVex] = false;
			eachPath.pop_back();
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
		CreateMatrix(output);
	}
}

void ALGraph::CreateMatrix(vector<string> &output)
{
	int start = stoi(output.front());
	int target = stoi(output.back().substr(output.back().find('>') + 1));

	edge[start][target] = output.size();

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

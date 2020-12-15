/*
 * -*- coding: utf-8 -*-
 * @Time    : 2020/12/14 20:36
 * @Author  : nieyuzhou
 * @File    : DataLoader.h/cpp
 * @Software: CLion
 */
#include "DataLoader.h"
Flight flight[2350];
int Flight::totalFlightNum = 0;

void HandleOriginData(const string &path)
{
	Flight::totalFlightNum = 0;
	ifstream data;
	data.open(path, ios::in);
	if (!data)
	{
		cout << "打开文件失败！" << endl;
		exit(1);
	}
	string line;
	int id = 1;
	getline(data, line);
	while (getline(data, line))   //整行读取，换行符“\n”区分，遇到文件尾标志eof终止读取
	{
		istringstream sin(line); //将整行字符串line读入到字符串流istringstream中
		vector<string> fields; //声明一个字符串向量
		string field;
		while (getline(sin, field, ',')) //将字符串流sin中的字符读入到field字符串中，以逗号为分隔符
		{
			fields.push_back(field); //将刚刚读取的字符串添加到向量fields中
		}
		stringstream temp;
		temp << fields[0];
		temp >> id;
		temp.clear();
		flight[id].flightId = id;
		flight[id].departureDate = fields[1];
		if (fields[2] == "Intl")
		{
			flight[id].intlorDome = false;
		}
		else
		{
			flight[id].intlorDome = true;
		}
		temp << fields[3];
		temp >> flight[id].flightNo;
		temp.clear();
		temp << fields[4];
		temp >> flight[id].departureAirport;
		temp.clear();
		temp << fields[5];
		temp >> flight[id].arrivalAirport;
		temp.clear();
		flight[id].departureTime = fields[6];
		flight[id].arrivalTime = fields[7];
		temp << fields[8];
		temp >> flight[id].airplaneId;
		temp.clear();
		temp << fields[9];
		temp >> flight[id].airplaneModel;
		temp.clear();
		temp << fields[10];
		temp >> flight[id].airFares;
		temp.clear();
	}
	Flight::totalFlightNum = id;
}
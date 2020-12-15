/*
 * -*- coding: utf-8 -*-
 * @Time    : 2020/12/14 16:51
 * @Author  : nieyuzhou
 * @File    : DataLoader.h/cpp
 * @Software: CLion
 */
#ifndef FLIGHT_SCHEDULING_DATALOADER_H
#define FLIGHT_SCHEDULING_DATALOADER_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <queue>
#include <stack>

using namespace std;
struct Flight
{
	static int totalFlightNum;
	bool intlorDome{};
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
};   //从1开始

void HandleOriginData(const string &path);


#endif //FLIGHT_SCHEDULING_DATALOADER_H

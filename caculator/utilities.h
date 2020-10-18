/*
 * -*- coding: utf-8 -*-
 * @Time    : 2020/10/4 23:17
 * @Author  : nieyuzhou
 * @File    : utilities.h/cpp
 * @Software: CLion
 */
#ifndef CALCULATOR_UTILITIES_H
#define CALCULATOR_UTILITIES_H

#include "iostream"
#include "vector"
#include "string"

using namespace std;
struct Data
{
	int parameter;
	int power;
};
struct LinearList
{
	Data *data;
	int length;
};
struct LinkList
{
	Data data;
	LinkList *next;
};

void parser(vector<string> &splited, LinearList &mainList);

void parser(vector<string> &splited, LinkList *&mainList);


vector<string> split(string &expression, char c1, char c2 = '\0');

void polyDisplay(LinearList &input);

void polyDisplay(LinkList *&input);

void vecDisplay(LinearList &input);

#endif //CALCULATOR_UTILITIES_H

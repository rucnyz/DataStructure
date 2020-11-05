/*
 * -*- coding: utf-8 -*-
 * @Time    : 2020/10/31 17:31
 * @Author  : nieyuzhou
 * @File    : expr.h/cpp
 * @Software: CLion
 */
#ifndef EXPR_EXPR_H
#define EXPR_EXPR_H


#include <iostream>
#include <stack>
#include <cmath>
#include <vector>

using namespace std;
#define ERROR 1
#define NORMAL 2
#define DEFINITION 3
#define RUN 4

extern vector<pair<string, string> > func;
using namespace std;

bool cmp(char &a, char &b);

template<typename T>
T calculate(T a, T b, char &op);

bool findLocalVar(string &expr, vector<string> &LocalVar);

bool isValidExpr(string &expr);

int calExpr(string &expr, double &result);

int preProcess(string &expr, double &value);

int process(string &expr, int flag, double value);

#endif //EXPR_EXPR_H

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

#define ERROR 1
#define NORMAL 2

using namespace std;

bool cmp(char &a, char &b);

template<typename T>
T calculate(T a, T b, char &op);

bool findLocalVar(string &expr, vector<string> &LocalVar);

bool isValidExpr(string &expr);

int calExpr(string &expr, double &result);


#endif //EXPR_EXPR_H

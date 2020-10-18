/*
 * -*- coding: utf-8 -*-
 * @Time    : 2020/9/28 18:09
 * @Author  : nieyuzhou
 * @File    : LinearList.h
 * @Software: CLion
 */
#ifndef CALCULATOR_LINEARLIST_H
#define CALCULATOR_LINEARLIST_H

#include <cmath>
#include <queue>
#include "utilities.h"


void initList(LinearList &L, string &expression, int a);

LinearList polyCal(LinearList &first, LinearList &second, char c);

LinearList polyPlus(LinearList &first, LinearList &second);

LinearList vecCal(LinearList &first, LinearList &second, char c);

LinearList grad(LinearList &input);

double cos(LinearList &first, LinearList &second);


#endif //CALCULATOR_LINEARLIST_H

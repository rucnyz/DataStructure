/*
 * -*- coding: utf-8 -*-
 * @Time    : 2020/10/5 0:16
 * @Author  : nieyuzhou
 * @File    : utilities.h/cpp
 * @Software: CLion
 */


#ifndef CALCULATOR_LINKLIST_H
#define CALCULATOR_LINKLIST_H

#include "utilities.h"
#include <queue>

void init(LinkList *&L);

void initList(LinkList *&L, string &expression);

void polyCal(LinkList *&first, LinkList *&second, LinkList *&result, char c);

void polyPlus(LinkList *&first, LinkList *&second, LinkList *&result);

void grad(LinkList *&input);


#endif //CALCULATOR_LINKLIST_H

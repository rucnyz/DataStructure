/*
 * -*- coding: utf-8 -*-
 * @Time    : 2020/11/6 15:29
 * @Author  : nieyuzhou
 * @File    : Matrix.h/cpp
 * @Software: CLion
 */
#ifndef EXPR_MATRIX_H
#define EXPR_MATRIX_H

#include <iostream>
#include <cmath>
#include <ctime>

using namespace std;
#define EPSILON 1e-14

bool isEqual(const double &_num1, const double &_num2);

typedef class Matrix
{
private:
	int m_row{};
	int m_col{};
	double *m_data{};

public:
	Matrix();

	Matrix(const int &_row, const int &_col, const double &_e = 0);

	Matrix(const int &_row, const int &_col, const double *_e);

	Matrix(const Matrix &_m);

	~Matrix();

	void release();

	bool isSquareMatrix() const;

	double *getRowPoint(const int &_r) const;

	double get(const int &_row, const int &_col) const;

	bool set(const int &_row, const int &_col, const double &_e) const;

	double getDet() const;

	Matrix inv_LU() const;

	Matrix eigenvalues() const;

	Matrix T() const;

	Matrix mul(const Matrix &_m) const;

	double operator()(const int &_row, const int &_col) const;

	Matrix &operator=(const Matrix &_m);

	friend Matrix operator+(const Matrix &_m1, const Matrix &_m2);

	friend Matrix &operator+=(Matrix &_m1, const Matrix &_m2);

	friend Matrix operator+(const Matrix &_m, const double &_e);

	friend Matrix operator+(const double &_e, const Matrix &_m);

	friend Matrix &operator+=(Matrix &_m, const double &_e);

	friend Matrix operator-(const Matrix &_m1, const Matrix &_m2);

	friend Matrix &operator-=(Matrix &_m1, const Matrix &_m2);

	friend Matrix operator-(const Matrix &_m, const double &_e);

	friend Matrix operator-(const double &_e, const Matrix &_m);

	friend Matrix &operator-=(Matrix &_m, const double &_e);

	friend Matrix operator*(const Matrix &_m1, const Matrix &_m2);

	friend Matrix operator*(const Matrix &_m, const double &_e);

	friend Matrix operator*(const double &_e, const Matrix &_m);

	friend Matrix &operator*=(Matrix &_m, const double &_e);

	friend Matrix operator/(const Matrix &_m, const double &_e);

	friend Matrix operator/(const Matrix &_m1, const Matrix &_m2);

	friend Matrix &operator/=(Matrix &_m, const double &_e);

	friend Matrix operator/(const double &_e, const Matrix &_m);

	friend ostream &operator<<(ostream &_out, const Matrix &_m);

protected:
	bool swapRow(const int &_i, const int &_j);

} matrix;    //	!matrix

Matrix processInput(string &input);

Matrix operator+(const Matrix &_m1, const Matrix &_m2);

Matrix &operator+=(Matrix &_m1, const Matrix &_m2);

Matrix operator+(const Matrix &_m, const double &_e);

Matrix operator+(const double &_e, const Matrix &_m);

Matrix &operator+=(Matrix &_m, const double &_e);

Matrix operator-(const Matrix &_m1, const Matrix &_m2);

Matrix &operator-=(Matrix &_m1, const Matrix &_m2);

Matrix operator-(const Matrix &_m, const double &_e);

Matrix operator-(const double &_e, const Matrix &_m);

Matrix &operator-=(Matrix &_m, const double &_e);

Matrix operator*(const Matrix &_m1, const Matrix &_m2);

Matrix operator*(const Matrix &_m, const double &_e);

Matrix operator*(const double &_e, const Matrix &_m);

Matrix &operator*=(Matrix &_m, const double &_e);

Matrix operator/(const Matrix &_m, const double &_e);

Matrix operator/(const Matrix &_m1, const Matrix &_m2);

Matrix &operator/=(Matrix &_m, const double &_e);

Matrix operator/(const double &_e, const Matrix &_m);

ostream &operator<<(ostream &_out, const Matrix &_m);


#endif //EXPR_MATRIX_H

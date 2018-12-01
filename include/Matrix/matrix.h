/*
 * 日期:	2018-12-1
 * 时间:	10:12
 * 姓名:	安帅
*/

#ifndef __MATRIX_H__
#define __MATRIX_H__
#include "define.h"
#include <iostream>
using namespace std;

MATRIX_BEGIN
template <typename T>
class Matrix
{
public:

	Matrix();

	Matrix(int m,int n);

	~Matrix();

private:
	int rows = 0;
	int cols = 0;
	T **M;
	
protected:	
public:
	template <typename T1>
	friend ostream &operator <<(ostream &out, Matrix<T1> &matrix);
};

MATRIX_END

#endif //__MATRIX_H__


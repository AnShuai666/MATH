/*
 * 日期:	2018-12-1
 * 时间:	10:12
 * 姓名:	安帅
*/

#include "Matrix/matrix.h"

MATRIX_BEGIN
	
	template <typename T>
	Matrix<T>::Matrix()
	{
		this->rows = 1;
		this->cols = 1;
		
		M = (int **) new int[this->rows];
		for(int i = 0; i < this->rows; i++)
		{
			M[i] = new int[this->cols];
		}

		for(int i = 0; i < this->rows; i++)
		{
			for(int j = 0; j < this->cols; j++)
			{
				M[i][j] = 0;
			}
		}
	}

	
	template <typename T>
	Matrix<T>::Matrix(int m, int n):rows(m),cols(n)
	{
		M = (int **) new T[this->rows];
		for(int i = 0; i < this->rows; i++)
		{
			M[i] = new T[this->cols];
		}
		for(int i = 0; i < this->rows; i++)
		{
			for(int j = 0; j < this->cols; j++)
			{
				cin>>M[i][j];
			}	
		}
	}

	
	template <typename T>
	Matrix<T>::~Matrix()
	{
		delete []M;
	}


	template <typename T1>
	ostream& operator <<(ostream &out, Matrix<T1> &matrix)
	{
		for(int i = 0; i < matrix.rows; i++)
		{
			for(int j = 0; j < matrix.cols; j++)
			{
				out << matrix.M[i][j] << " ";
			}
			out << endl;
		}
		return out;
	}


MATRIX_END



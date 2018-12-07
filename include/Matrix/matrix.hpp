/*
 * 日期:	2018-12-1
 * 时间:	10:12
 * 姓名:	安帅
*/


#ifndef __MATRIX_H__
#define __MATRIX_H__
#include "define.h"
#include <iostream>
#include <memory>
using namespace std;

MATRIX_NAMESPACE_BEGIN
template <typename T, int m, int n>
class Matrix
{
public:
    //静态变量开始进行初始化，constexpr rows 与cols不变
    static int constexpr rows = m;
    static int constexpr cols = n;

    //默认构造函数
	Matrix(void);

	/* 一般构造函数
	 * 行主序，用一个已有的数组（m*n的矩阵）来初始化矩阵
	 * @param_in   arr  输入数组
	 */
	Matrix(T const *arr);

	/* 一般构造函数
	 * 对矩阵进行初始化，值全为value
	 * @param_in    value   输入值
	*/
	Matrix(T const &value);


	//TODO(1): 加const关键字防止更改参数
	Matrix( Matrix& );

	~Matrix();

	//TODO(3):直接在主函数输入的函数实现
	void input()
    {
	    for(int i = 0; i < this->rows; i++)
        {
            for(int j = 0; j < this->cols; j++)
            {
                cin >> this->M[i][j];
            }
            //TODO(4):实时检测键盘输入数字的个数,有一行的数之后执行下面语句
            //cout<<endl;
        }

    }

private:


	enum NORM_TYPE
    {
	    L1,
	    L2,
	    L0 //L0表示无穷范数
    };
	
protected:
    T M[m * n];
public:

    inline int getRows()
    {
        return this->rows;
    };

    inline int getCols()
    {
        return  this->cols;
    };

	template <typename T1>
	friend ostream &operator <<(ostream &out, Matrix<T1> &matrix);

	//TODO(2): 矩阵重载运算符的实现
	template <typename T1>
    T1 * operator [](int index)
    {
        return this->M[index];
    };

	Matrix<T> &operator +(Matrix<T> &matrix)
    {
	    if(this->rows != matrix.getRows() || this->cols != matrix.getCols())
        {
	        std::cerr<<"两个矩阵不匹配!"<<endl;
	        std::exit(0);
        }
        Matrix<T> *tmp = new Matrix(this->rows,this->cols);

        for (int i = 0; i < this->rows; ++i)
        {
            for (int j = 0; j < this->cols; ++j)
            {
                tmp->M[i][j] = this->M[i][j] + matrix.M[i][j];
            }
        }
        return *tmp;
    }

    Matrix<T> &operator -(Matrix<T> &matrix)
    {
        if(this->rows != matrix.getRows() || this->cols != matrix.getCols())
        {
            std::cerr<<"两个矩阵不匹配!"<<endl;
            std::exit(0);
        }

        Matrix<T> *tmp = new Matrix(this->rows,this->cols);

        for (int i = 0; i < this->rows; ++i)
        {
            for (int j = 0; j < this->cols; ++j)
            {
                tmp->M[i][j] = this->M[i][j] - matrix.M[i][j];
            }
        }
        return *tmp;
    }

    //TODO(5): 矩阵乘法
    Matrix<T> &operator *(Matrix<T> &matrix)
    {
	    if(this->cols != matrix.getRows() )
        {
	        cerr<<"矩阵类型不匹配,不能进行矩阵乘法!"<<endl;
	        //TODO(12):查exit函数参数意义
	        exit(0);
        }
        
        Matrix<T> *tmp = new Matrix(this->rows,matrix.getCols());
	    //int sum = 0;
        for (int i = 0; i < tmp->rows; ++i)
        {
            for (int j = 0; j < tmp->getCols(); ++j)
            {
                for (int k = 0; k < this->cols; ++k)
                {

                    tmp->M[i][j] +=this ->M[i][k]*matrix.M[k][j];

                }
            }

        }
        return *tmp;
    }
    //TODO(6): 矩阵点除
    Matrix<T> &operator /(Matrix<T> &matrix);

    //TODO(7): 转置矩阵
    Matrix<T> &transpose()
    {
	    Matrix<T> *tmp;
        return ;
    }



    //TODO(8): 伴随矩阵
    Matrix<T> &adjoint();


    //TODO(9): 逆矩阵
    Matrix<T> &inverse();


    //TODO(10): 矩阵的迹要判断是否为方阵
    int trace();



    //TODO(11): 矩阵范数 用枚举类型
    int norm(enum NORM_TYPE norm_type);



    //TODO(13): 行列式
    int determiniant();

    //  TODO(14): 矩阵特征值

    // TODO(15): 特征向量

};






MATRIX_NAMESPACE_END

#endif //__MATRIX_H__



MATRIX_NAMESPACE_BEGIN

    template <typename T, int m, int n>
    Matrix<T,m,n>::Matrix()
    {

    }


    template <typename T,int m, int n>
    Matrix<T,m,n>::Matrix(T const *arr)
    {
        std::copy(arr,arr + m * n,M);
    }

    template <typename T, int m, int n>
    Matrix<T,m,n>::Matrix(const T &value)
    {
        
    }

    template <typename T>
    Matrix<T>::Matrix( Matrix& matrix1)
    {
        this->rows = matrix1.getRows();
        this->cols = matrix1.getCols();

        M = (T **) new T(this->rows);
        for (int i = 0; i < this->rows; ++i)
        {
            M[i] = new T[this->cols];
        }

        for (int j = 0; j < this->rows; ++j)
        {
            for (int k = 0; k < this->cols; ++k)
            {
                M[j][k] =matrix1.M[j][k];
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


    MATRIX_NAMESPACE_END

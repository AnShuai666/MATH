/*
 * 日期:	2018-12-1
 * 时间:	10:12
 * 姓名:	安帅
 * @func    矩阵类 矩阵常规运算
*/


#ifndef __MATRIX_H__
#define __MATRIX_H__
#include "define.h"
#include <iostream>
#include <memory>
#include <algorithm>
using namespace std;

MATRIX_NAMESPACE_BEGIN
/********************************************************************
 *~~~~~~~~~~~~~~~~~~~~~常用矩阵类型别名声明~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *******************************************************************/
    template <typename T, int m ,int n> class Matrix;
    typedef Matrix<int,2,2> Matrix2i;
    typedef Matrix<int,3,3> Matrix3i;
    typedef Matrix<int,4,4> Matrix4i;
    typedef Matrix<unsigned int,2,2> Matrix2ui;
    typedef Matrix<unsigned int,3,3> Matrix3ui;
    typedef Matrix<unsigned int,4,4> Matrix4ui;
    typedef Matrix<float ,2,2> Matrix2f;
    typedef Matrix<float ,3,3> Matrix3f;
    typedef Matrix<float ,4,4> Matrix4f;
    typedef Matrix<double ,2,2> Matrix2d;
    typedef Matrix<double ,3,3> Matrix3d;
    typedef Matrix<double ,4,4> Matrix4d;

/********************************************************************
 *~~~~~~~~~~~~~~~~~~~~~~~~~Matrix类的声明~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *******************************************************************/
    template <typename T,int m, int n>
    class Matrix
    {
    public:
        typedef shared_ptr<Matrix<T,m,n>> Ptr;
        //声明矩阵行列，static保证必须初始化时给定行列值
        static int constexpr rows = m;
        static int constexpr cols = n;

/********************************************************************
 *~~~~~~~~~~~~~~~~~~~~~构造函数与析构函数~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *******************************************************************/


        /*
         *  @property   默认构造函数
         *  @func       对矩阵的rows与cols进行初始化
        */
        Matrix();

        /*
         *  @property   普通构造函数
         *  @func       用存在的矩阵（m*n的数组）进行初始化
         *  @exlpicit   防止隐式转换修改成员参数值
         *  @param_in   arr
        */
        explicit Matrix(T const *arr);

        /*
         *  @property   普通构造函数
         *  @func       用value对矩阵（m*n的数组）进行初始化
         *  @exlpicit   防止隐式转换修改成员参数值
         *  @param_in   value
        */
        explicit Matrix(T const value);

        /*
         *  @property   拷贝构造函数
         *  @func       用同一类型的vector1matrix1对矩阵（m*n的数组）进行初始化
         *  @param_in   matrix1
        */
        Matrix(Matrix<T,m,n> const& matrix1);

        /*
         *  @property   拷贝构造函数
         *  @func       用任意类型的matrix1对矩阵（m*n的数组）进行初始化
         *  @param_in   matrix1
        */
        template <typename T1>
        Matrix(Matrix<T1,m,n> const &matrix1);

        /*
         *  @property   析构函数
         *  @func       释放M内存
        */
        ~Matrix();

/********************************************************************
 *~~~~~~~~~~~~~~~~~~~~~构造函数与析构函数~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *******************************************************************/
    public:
        /*
         *  @property   判断函数
         *  @func       判断矩阵是否为方阵
         *  @const      声明为const函数，防止更改成员变量以及非常成员函数
        */
        bool is_square_matrix() const;



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

/********************************************************************
 *~~~~~~~~~~~~~~~~~~~~~~~~矩阵运算符重载~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *******************************************************************/
    public:

        /*
         *  @property   矩阵解引用
         *  @func       对矩阵构成的数组解引用
         *  @return     T*
        */
        T *operator*();

        /*
         *  @property   矩阵解引用
         *  @func       对常矩阵构成的数组解引用
         *  @return     T*
        */
        T const* operator*() const;

        /*
         *  @property   矩阵元素访问
         *  @func       对矩阵元素进行访问matrix（m,n）
         *  @param_in   row     矩阵行索引
         *  @param_in   col     矩阵列索引
         *  @return     T&      避免产生临时变量，返回引用与返回值共用一个地址
        */
        T& operator()(int row,int col);

        /*
         *  @property   常矩阵元素访问
         *  @func       对常矩阵元素进行访问matrix（m,n）
         *  @param_in   row         矩阵行索引
         *  @param_in   col         矩阵列索引
         *  @return     T const&    避免产生临时变量，返回引用与返回值共用一个地址
        */
        T const& operator()(int row, int col) const;

        /*
         *  @property   矩阵元素线性访问
         *  @func       对矩阵元素进行线性访问matrix（i）
         *  @param_in   i       数组表示的矩阵中，数组的索引值
         *  @return     T&      避免产生临时变量，返回引用与返回值共用一个地址
        */
        T& operator[](unsigned int i);

        /*
        *  @property   常矩阵元素线性访问
        *  @func       对常矩阵元素进行线性访问matrix（i）
        *  @param_in   i            数组表示的矩阵中，数组的索引值
        *  @return     T const&     避免产生临时变量，返回引用与返回值共用一个地址
        */
        T const& operator[](unsigned int i) const;

        /*
        *  @property   矩阵加法
        *  @func       对两个矩阵对应元素进行相加
        *  @param_in   matrix1          被加矩阵
        *  @return     Matrix<T,m,n>&   避免产生临时变量，返回引用与返回值共用一个地址
        */
        Matrix<T,m,n>& operator+= (Matrix<T,m,n> const& matrix1);

        /*
        *  @property   矩阵加法
        *  @func       对两个矩阵对应元素进行相加
        *  @param_in   matrix1          被加矩阵
        *  @return     Matrix<T,m,n>&   避免产生临时变量，返回引用与返回值共用一个地址
        */
        Matrix<T,m,n>& operator+ (Matrix<T,m,n> const& matrix1) const;

        /*
        *  @property   矩阵加法
        *  @func       对矩阵中每个元素加上相同数值
        *  @param_in   value            被加矩阵
        *  @return     Matrix<T,m,n>&   避免产生临时变量，返回引用与返回值共用一个地址
        */
        Matrix<T,m,n>& operator+= (T const& value);

        /*
        *  @property   矩阵加法
        *  @func       对矩阵中每个元素加上相同数值
        *  @param_in   value            被加矩阵
        *  @return     Matrix<T,m,n>&   避免产生临时变量，返回引用与返回值共用一个地址
        */
        Matrix<T,m,n>& operator+ (T const& value) const;

        /*
        *  @property   矩阵减法
        *  @func       对两个矩阵对应元素进行相减
        *  @param_in   matrix1          被减矩阵
        *  @return     Matrix<T,m,n>&   避免产生临时变量，返回引用与返回值共用一个地址
        */
        Matrix<T,m,n>& operator-= (Matrix<T,m,n> const& matrix1);

        /*
        *  @property   矩阵减法
        *  @func       对两个矩阵对应元素进行相减
        *  @param_in   matrix1          被减矩阵
        *  @return     Matrix<T,m,n>&   避免产生临时变量，返回引用与返回值共用一个地址
        */
        Matrix<T,m,n>& operator- (Matrix<T,m,n> const& matrix1) const;

        /*
        *  @property   矩阵减法
        *  @func       对矩阵中每个元素减去相同数值
        *  @param_in   value            被减矩阵
        *  @return     Matrix<T,m,n>&   避免产生临时变量，返回引用与返回值共用一个地址
        */
        Matrix<T,m,n>& operator-= (T const& value);

        /*
        *  @property   矩阵减法
        *  @func       对矩阵中每个元素减去相同数值
        *  @param_in   value            被减矩阵
        *  @return     Matrix<T,m,n>&   避免产生临时变量，返回引用与返回值共用一个地址
        */
        Matrix<T,m,n>& operator- (T const& value) const;

        /*
        *  @property   矩阵乘法
        *  @func       M(m*n)xM(n*l)= M(m*l)
        *  @param_in   matrix1          被乘矩阵
        *  @return     Matrix<T,m,l>&   避免产生临时变量，返回引用与返回值共用一个地址
        */
        template <int l>
        Matrix<T,m,l>& operator* (Matrix<T,n,l> matrix1) const;




        //TODO(7): 转置矩阵
        Matrix<T,m,n> &transpose()
        {
            Matrix<T,m,n> *tmp;
            return ;
        }



        //TODO(8): 伴随矩阵
        Matrix<T,m,n> &adjoint();


        //TODO(9): 逆矩阵
        Matrix<T,m,n> &inverse();


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
    template <typename T,int m,int n>
    inline
    Matrix<T,m,n>::Matrix()
    {

    }

    template <typename T,int m, int n>
    inline
    Matrix<T,m,n>::Matrix(T const *arr)
    {
        std::copy(arr,arr + m * n,M);
    }

    template <typename T, int m, int n>
    inline
    Matrix<T,m,n>::Matrix(T const value)
    {
        std::fill(M,M + m*n, value);
    }

    template <typename T, int m,int n>
    inline
    Matrix<T,m,n>::Matrix(Matrix<T,m,n> const& matrix1)
    {
        std::copy(matrix1.M, matrix1.M + m * n, M);
    }

    template <typename T,int m,int n>
    template <typename T1>
    Matrix<T,m,n>::Matrix(Matrix<T1,m,n> const &matrix1)
    {
        std::copy(matrix1.M, matrix1.M + m * n, M);
    }


    template <typename T, int m, int n>
    Matrix<T,m,n>::~Matrix()
    {
        delete []M;
    }

    template <typename T, int m, int n>
    inline bool
    Matrix<T,m,n>::is_square_matrix() const
    {

    }

    template <typename T, int m, int n>
    inline T*
    Matrix<T,m,n>::operator*()
    {
        return M;
    }

    template <typename T,int m,int n>
    inline T const*
    Matrix<T,m,n>::operator*() const
    {
        return M;
    }

    template <typename T,int m,int n>
    inline T&
    Matrix<T,m,n>::operator()(int row,int col)
    {
        return M[row * m + col];
    }
    template <typename T,int m,int n>
    inline T const&
    Matrix<T,m,n>::operator()(int row, int col) const
    {
        return M[row * m + n];
    }

    template <typename T,int m,int n>
    inline T&
    Matrix<T,m,n>::operator[](unsigned int i)
    {
        return M[i];
    }

    template <typename T,int m,int n>
    inline T const&
    Matrix<T,m,n>::operator[](unsigned int i) const
    {
        return M[i];
    }

    template <typename T,int m, int n>
    inline Matrix<T,m,n>&
    Matrix<T,m,n>::operator+= (Matrix<T,m,n> const& matrix1)
    {
        std::transform(M,M + m *n, *matrix1, M, std::plus<T>());
        return *this;
    }

    template <typename T,int m,int n>
    inline Matrix<T,m,n>&
    Matrix<T,m,n>::operator+ (Matrix<T,m,n> const& matrix1) const
    {
        std::transform(M,M + m * n, *matrix1,M,std::plus<T>());
        return *this;
    }

    template <typename T,int m, int n>
    inline Matrix<T,m,n>&
    Matrix<T,m,n>::operator+= (T const& value)
    {
        for(auto a : M)
        {
            a+=value;
        }
    }

    template <typename T,int m,int n>
    inline Matrix<T,m,n>&
    Matrix<T,m,n>::operator+ (T const& value) const
    {
        for(auto a : M)
            a += value;
    }

    template <typename T,int m, int n>
    inline Matrix<T,m,n>&
    Matrix<T,m,n>::operator-= (Matrix<T,m,n> const& matrix1)
    {
        std::transform(M,M + m *n, *matrix1, M, std::minus<T>());
        return *this;
    }

    template <typename T,int m,int n>
    inline Matrix<T,m,n>&
    Matrix<T,m,n>::operator- (Matrix<T,m,n> const& matrix1) const
    {
        std::transform(M,M + m * n, *matrix1,M,std::minus<T>());
        return *this;
    }

    template <typename T,int m, int n>
    inline Matrix<T,m,n>&
    Matrix<T,m,n>::operator-= (T const& value)
    {
        for(auto a : M)
        {
            a-=value;
        }
    }

    template <typename T,int m,int n>
    inline Matrix<T,m,n>&
    Matrix<T,m,n>::operator- (T const& value) const
    {
        for(auto a : M)
            a -= value;
    }

    template <typename T,int m, int n>
    template <int l>
    inline Matrix<T,m,l>&
    Matrix<T,m,n>::operator* (Matrix<T,n,l> matrix1) const
    {
        static Matrix<T,m,l> matrix2 ;

        for (int i = 0; i < m; ++i)
        {
            for (int j = 0; j <l ; ++j)
            {
                T sum=0;
                for (int k = 0; k < n; ++k)
                {
                    sum+=M[i*cols+k]*matrix1.M[k*matrix1.cols+j];
                }
                matrix2.M[i*matrix2.cols+j]=sum;
            }

        }
        return matrix2 ;
    }



MATRIX_NAMESPACE_END
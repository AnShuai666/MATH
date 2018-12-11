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
#include "Matrix/vector.hpp"
using namespace std;
using namespace matrix;
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
       // ~Matrix();



/********************************************************************
*~~~~~~~~~~~~~~~~~~~~~~~~Matrix迭代器~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
********************************************************************/
    public:
        /*
        *  @property   迭代器
        *  @func       代表矩阵第一个元素的指针
        *  @return     T*
        */
        T* begin();

        /*
        *  @property   迭代器
        *  @func       代表矩阵第一个元素的指针
        *  @const      防止修改返回指针
        *  @const2     防止修改类变量
        *  @return     T const*
        */
        T const* begin() const;

        /*
        *  @property   迭代器
        *  @func       代表矩阵最后一个元素的指针的下一个
        *  @return     T*
        */
        T* end();

        /*
        *  @property   迭代器
        *  @func       代表矩阵最后一个元素的指针的下一个
        *  @const1     防止修改返回指针
        *  @const2     防止修改类变量
        *  @return     T const*
        */
        T const* end() const;


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
        *  @return     Matrix<T,m,l>    避免产生临时变量，返回引用与返回值共用一个地址
        */
        template <int l>
        Matrix<T,m,l> operator* (Matrix<T,n,l> matrix1) const;

        /*
        *  @property   矩阵乘法
        *  @func       M(m*n)xV(n*1)= V(m*1)
        *  @param_in   vector1          被乘向量
        *  @return     Matrix<T,m,l>&
        */
        Vector<T,m> operator* (Vector<T,n> const & vector1) const;

        /*
        *  @property   矩阵乘法
        *  @func       M(m*n)*a             原矩阵被改变
        *  @param_in   T                    被乘数
        *  @return     Matrix<T,m,n>&
        */
        Matrix<T,m,n>& operator*= (T const& num);

        /*
        *  @property   矩阵乘法               原矩阵不被改变
        *  @func       M(m*n)*a
        *  @param_in   T                    被乘数
        *  @return     Matrix<T,m,n>
        */
        Matrix<T,m,n> operator* (T const& num) const;

        /*
        *  @property   矩阵除法
        *  @func       M(m*n)/a             原矩阵被改变
        *  @param_in   T                    被乘数
        *  @return     Matrix<T,m,n>&
        */
        Matrix<T,m,n>& operator/= (T const& num);

        /*
        *  @property   矩阵乘法               原矩阵不被改变
        *  @func       M(m*n)xa
        *  @param_in   T                    被除数
        *  @return     Matrix<T,m,n>
        */
        Matrix<T,m,n> operator/ (T const& num) const;


        /*
        *  @property   重载运算符<<  必须重新定义模板
        *  @func       输出运算符
        *  @param_in   Matrix<T1,m1,n1>&
        *  @param_out  out
        *  @return     ostream &
        */
        template <typename T1,int m1,int n1>
        friend ostream & operator<< (ostream& out,const Matrix<T1,m1,n1>& matrix1);

/********************************************************************
*~~~~~~~~~~~~~~~~~~~~~Matrix管理函数~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
********************************************************************/
    public:
        /*
        *  @property   方阵判断
        *  @func       判断是否为方阵， 是 返回True
        *  @return     bool
        */
        bool is_square() const;

        /*
        *  @property   求最小值
        *  @func       求矩阵最小值
        *  @return     T
        */
        T minimum() const;

        /*
        *  @property   求最大值
        *  @func       求矩阵最大值
        *  @return     T
        */
        T maximum() const;

        /*
        *  @property   求矩阵行
        *  @func       获取矩阵第index行
        *  @return     Vector<T,n>
        */
        Vector<T,n> row(int index) const;

        /*
        *  @property   求矩阵列
        *  @func       获取矩阵第index列
        *  @return     Vector<T,m>
        */
        Vector<T,m> col(int index) const;


        template <int l>
        Matrix<T,m,n + l> hstack(Matrix<T,m,l> const& matrix1) const;

        template <int l>
        Matrix<T,m + l,n> vstack(Matrix<T,l,n> const& matrix1) const;

        Matrix<T,m,n + 1> hstack(Vector<T,m> const& vector1) const;

        Matrix<T,m + 1,n> vstack(Vector<T,n> const& vector1) const;

        Matrix<T,m - 1,n> delete_row(int index) const;

        Matrix<T,m,n - 1> delete_col(int index) const;


/********************************************************************
*~~~~~~~~~~~~~~~~~~~~~~Vector一元运算~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
********************************************************************/
    public:
    Matrix<T,m,n>& negate();

    Matrix<T,m,n> negated() const;

    Matrix<T,m,n>& transpose();

    Matrix<T,m,n> transposed() const;


/********************************************************************
*~~~~~~~~~~~~~~~~~~~~~~Vector二元运算~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
********************************************************************/
    public:

        bool is_similar(Matrix<T,m,n> const& matrix1, T const& eps) const;


    protected:
        T M[m * n];









        //TODO(8): 伴随矩阵
        Matrix<T,m,n> &adjoint();


        //TODO(9): 逆矩阵
        Matrix<T,m,n> &inverse();


        //TODO(10): 矩阵的迹要判断是否为方阵
        int trace();



        //TODO(11): 矩阵范数 用枚举类型
        enum NORM_TYPE{l1,l2};
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

    /*
    template <typename T, int m, int n>
    Matrix<T,m,n>::~Matrix()
    {
        delete []M;
    }
    */


    template <typename T,int m,int n>
    inline T*
    Matrix<T,m,n>::begin (void)
    {
        return M;
    }

    template <typename T,int m,int n>
    inline T const*
    Matrix<T,m,n>::begin (void) const
    {
        return M;
    }

    template <typename T,int m,int n>
    inline T*
    Matrix<T,m,n>::end (void)
    {
        return M + m * n;
    }

    template <typename T,int m,int n>
    inline T const*
    Matrix<T,m,n>::end (void) const
    {
        return M + m * n;
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
        return M[row * m + col];
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
            for(auto& a : M)
            {
                a+=value;
            }
    }

    template <typename T,int m,int n>
    inline Matrix<T,m,n>&
    Matrix<T,m,n>::operator+ (T const& value) const
    {
        for(auto& a : M)
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
    inline Matrix<T,m,l>
    Matrix<T,m,n>::operator* (Matrix<T,n,l> matrix1) const
    {
        Matrix<T,m,l> matrix2 ;

        for (int i = 0; i < m; ++i)
        {
            for (int j = 0; j <l ; ++j)
            {
                T sum = 0;
                for (int k = 0; k < n; ++k)
                {
                    sum+=M[i*cols+k]*matrix1.M[k*matrix1.cols+j];
                }
                matrix2.M[i*matrix2.cols+j] = sum;
            }
        }
        return matrix2;
    }

    template <typename T,int m, int n>
    inline Vector<T,m>
    Matrix<T,m,n>::operator* (Vector<T,n> const& vector1) const
    {
        Vector<T,m> tmp(0);
        for (int i = 0; i < m; ++i)
        {
            tmp[i] = std::inner_product(M*i,M*i+n,*vector1,T(0));
        }
        return tmp;
    }

    template <typename T,int m, int n>
    inline Matrix<T,m,n>&
    Matrix<T,m,n>::operator*= (T const& num)
    {
        for(auto& a : this->M)
            a *= num;
        return *this;
    }

    template <typename T,int m, int n>
    inline Matrix<T,m,n>
    Matrix<T,m,n>::operator* (T const& num) const
    {
        return Matrix<T,m,n>(*this)*=num;
    }

    template <typename T,int m, int n>
    inline Matrix<T,m,n>&
    Matrix<T,m,n>::operator/= (T const& num)
    {
        for(auto& a : this->M)
            a /= num;
        return *this;
    }

    template <typename T,int m, int n>
    inline Matrix<T,m,n>
    Matrix<T,m,n>::operator/ (T const& num) const
    {
        return Matrix<T,m,n>(*this)/=num;
    }

    template <typename T,int m,int n>
    ostream& operator<< (ostream& out,const Matrix<T,m,n>& matrix1)
    {
        out<<endl;
        for (int i = 0; i < m; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                out<<matrix1(i,j)<<" ";
            }
            out<<endl;
        }
        return out;
    }

    template <typename T, int m,int n>
    inline bool
    Matrix<T,m,n>::is_square() const
    {
        return m == n;
    }

    template <typename T, int m,int n>
    inline T
    Matrix<T,m,n>::minimum() const
    {
        return *std::min_element(M,M + m * n);
    }

    template <typename T, int m,int n>
    inline T
    Matrix<T,m,n>::maximum() const
    {
        return *std::max_element(M,M + m * n);
    }

    template <typename T, int m,int n>
    inline Vector<T,n>
    Matrix<T,m,n>::row(int index) const
    {
        return Vector<T,n>(M + n * index);
    }

    template <typename T, int m,int n>
    inline Vector<T,m>
    Matrix<T,m,n>::col(int index) const
    {
        Vector<T,m> tmp(0);
        for (int i = 0; i < m ; i ++)
        {
            tmp(i) = M(i,index);
        }
        return tmp;
    }

    template <typename T,int m,int n>
    template <int l>
    inline Matrix<T,m,n + l>
    Matrix<T,m,n>::hstack(Matrix<T,m,l> const& matrix1) const
    {

    }

    template <typename T,int m,int n>
    template <int l>
    inline Matrix<T,m + l,n>
    Matrix<T,m,n>::vstack(Matrix<T,l,n> const& matrix1) const
    {

    }

    template <typename T,int m,int n>
    inline Matrix<T,m,n + 1>
    Matrix<T,m,n>::hstack(Vector<T,m> const& vector1) const
    {

    }

    template <typename T,int m,int n>
    inline Matrix<T,m + 1,n>
    Matrix<T,m,n>::vstack(Vector<T,n> const& vector1) const
    {

    }

    template <typename T,int m,int n>
    inline Matrix<T,m - 1,n>
    Matrix<T,m,n>::delete_row(int index) const
    {

    }

    template <typename T,int m,int n>
    inline Matrix<T,m,n - 1>
    Matrix<T,m,n>::delete_col(int index) const
    {

    }


    template <typename T,int m,int n>
    inline Matrix<T,m,n>&
    Matrix<T,m,n>::negate()
    {

    }

    template <typename T,int m,int n>
    inline Matrix<T,m,n>
    Matrix<T,m,n>::negated() const
    {

    }

    template <typename T,int m,int n>
    inline Matrix<T,m,n>&
    Matrix<T,m,n>::transpose()
    {

    }

    template <typename T,int m,int n>
    inline Matrix<T,m,n>
    Matrix<T,m,n>::transposed() const
    {

    }

    template <typename T,int m,int n>
    inline bool
    Matrix<T,m,n>::is_similar(Matrix<T,m,n> const& matrix1, T const& eps) const
    {

    }


MATRIX_NAMESPACE_END
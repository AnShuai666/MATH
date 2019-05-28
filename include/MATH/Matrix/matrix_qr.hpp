/*
 * 日期:	2018-04-09
 * 时间:	10:56
 * 姓名:	安帅
 * @func    矩阵QR分解运算
*/

/*
 *  矩阵QR分解，也称为正三角分解，是一种特殊的三角分解，在解决矩阵特征值的计算、
 *  最小二乘等问题起到重要作用。
 *  QR分解定理： 任意一个满秩实（复）矩阵A，都可唯一地分解A = QR,其中，
 *  Q为正交（酉）矩阵，R是具有正对角元的上三角矩阵
 *
*/

#ifndef MATH_MATRIX_QR_HPP
#define MATH_MATRIX_QR_HPP

#include <MATH/math_define.h>
#include "define.h"
#include "matrix.hpp"
#include "vector.hpp"
MATH_NAMESPACE_BEGIN
MATRIX_NAMESPACE_BEGIN

/*
 *  @property   QR分解
 *  @func       将矩阵A进行QR分解
 *  @param_in   A           待分解矩阵A(MxN)
 *  @param_in   rows        矩阵行数
 *  @param_in   cols        矩阵列数
 *  @param_in   Q           正交矩阵(MxM)
 *  @param_in   R           正对角元上三角矩阵(MxN)
 *  @param_in   episilon
*/
#if 0
template <typename T>
void qr_decomposition(T const* A,int rows,int col,T* Q,T* R,T const& epsilon = T(1e-12));
#endif
template <typename T,int m,int n>
void qr_decomposition(Matrix<T,m,n> *A,Matrix<T,m,m>* Q,Matrix<T,m,n>* R,T const& epsilon = T(1e-12));
MATRIX_NAMESPACE_END
MATH_NAMESPACE_END


MATH_NAMESPACE_BEGIN
MATRIX_NAMESPACE_BEGIN

//TODO:@邹云龙 实现之过程重要步骤注释
//TODO:没有实现动态模板，矩阵不能初始化，函数未能测试。
#if 0
template <typename T>
void
math::matrix::qr_decomposition(T const* A, int rows, int cols,T* Q,T* R,T const& epsilon )
{

    Matrix<T,rows,cols> matrix_A(A),matrix_R;
    Matrix<T,rows,rows> matrix_Q;
    qr_decomposition(matrix_A,Q,R,epsilon);

}
#endif
template <typename T,int m,int n>
void
math::matrix::qr_decomposition(Matrix<T,m,n> *A,Matrix<T,m,m>* Q,Matrix<T,m,n>* R,T const& epsilon )
{
   //施密特方法
    for (int i = 0; i < n; ++i)
    {
        Vector<T,m> x = A->col(i);
        for (int j = 0; j < i; ++j)
        {
            x-=A->col(i).dot(Q->col(j))*Q->col(j)/Q->col(j)*Q->col(j);
        }
        Q->col(i)=x;
    }
  //正交化
    for (int k = 0; k <n; ++k)
    {
        double dev=Q->col(k).dot(Q->col(k));
        dev < epsilon ? Q->col(k)*=0:Q->col(k)/=sqrt(dev);
    }
    R = Q->transpose()*A;
}

MATRIX_NAMESPACE_END
MATH_NAMESPACE_END
#endif //MATH_MATRIX_QR_HPP

/*
 * 日期:	2018-04-09
 * 时间:	10:58
 * 姓名:	安帅
 * @func    矩阵SVD分解
*/

#ifndef MATH_MATRIX_SVD_HPP
#define MATH_MATRIX_SVD_HPP

#include <MATH/math_define.h>
#include "define.h"
MATH_NAMESPACE_BEGIN
MATRIX_NAMESPACE_BEGIN

/*
 *  @property   SVD分解
 *  @func       将矩阵A进行SVD分解
 *  @param_in   A           待分解矩阵A(MxN)
 *  @param_in   rows        矩阵行数
 *  @param_in   cols        矩阵列数
 *  @param_in   U           正交矩阵(MxM)
 *  @param_in   S           正对角元上三角矩阵(MxN)
 *  @param_in   V           正交矩阵(NxN)
 *  @param_in   episilon
*/
template <typename T>
void svd_decomposition(T const* A,int rows,int coll,T* U,T* S,T* V,T const& epsilon = T(1e-12));


MATRIX_NAMESPACE_END
MATH_NAMESPACE_END


MATH_NAMESPACE_BEGIN
    MATRIX_NAMESPACE_BEGIN

//TODO:     @杜靖
//TODO:     任务：实现之,重要过程步骤注释,下载PPT讲解原理及函数使用方法
//TODO:     截止日期：周五下班前
template <typename T>
void
math::matrix::svd_decomposition(T const *A, int rows, int coll, T *U, T *S, T *V, const T &epsilon)
{

}



MATRIX_NAMESPACE_END
MATH_NAMESPACE_END
#endif //MATH_MATRIX_SVD_HPP

/*
 * 日期:	2018-04-09
 * 时间:	09:58
 * 姓名:	安帅
 * @func    矩阵cholesky相关运算
*/

#ifndef MATH_CHOLESKY_HPP
#define MATH_CHOLESKY_HPP

#include <math_define.h>
#include "define.h"
MATH_NAMESPACE_BEGIN
MATRIX_NAMESPACE_BEGIN

/*
 *  @property   Cholesky分解
 *  @func       将矩阵A进行Cholesky分解
 *  @param_in   A       待分解矩阵A
 *  @param_in   cols    矩阵列数
 *  @param_in   L       A的下三角矩阵
*/
template <typename T>
void
cholesky_decomposition(T const* A,int const cols,T* L);





MATRIX_NAMESPACE_END
MATH_NAMESPACE_END


MATH_NAMESPACE_BEGIN
MATRIX_NAMESPACE_BEGIN
//TODO: FOR 邹云龙实现并写一个该文件的一个api文档，去查一下api如何写
/*
 * template <typename T>
void
cholesky_decomposition (T const* A, int const cols, T* L)
{
    T* out_ptr = L;
    for (int r = 0; r < cols; ++r)
    {

        for (int c = 0; c < r; ++c)
    {
        T result = T(0);
        for (int ci = 0; ci < c; ++ci)
        result += L[r * cols + ci] * L[c * cols + ci];
        result = A[r * cols + c] - result;
        (*out_ptr++) = result / L[c * cols + c];
    }


{
    T* L_row_ptr = L + r * cols;
    T result = T(0);
    for (int c = 0; c < r; ++c)
    result += MATH_POW2(L_row_ptr[c]);
    result = std::max(T(0), A[r * cols + r] - result);
    (*out_ptr++) = std::sqrt(result);
}

for (int c = r + 1; c < cols; ++c)
(*out_ptr++) = T(0);
}
}
 *
 * */
template<typename T>    
void 
math::matrix::cholesky_decomposition(T const *A, int const cols, T *L) 
{
    T* out_ptr = L;
    //TODO:CUDA@杨丰拓
    //计算下三角对角线左侧数据
    for (int i = 0; i < ; ++i)
    {
        
    }

    //计算下三角对角线数据
    for (int j = 0; j < ; ++j) {

    }

    //填充下三角右侧数据项为0
    for (int k = 0; k < ; ++k) {

    }

}
    
MATRIX_NAMESPACE_END
MATH_NAMESPACE_END
#endif //MATH_CHOLESKY_HPP

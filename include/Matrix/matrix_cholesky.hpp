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

/*
 * 日期:	2018-04-09
 * 时间:	09:58
 * 姓名:	安帅
 * @func    矩阵cholesky相关运算
*/

#ifndef MATH_CHOLESKY_HPP
#define MATH_CHOLESKY_HPP

#include "math_define.h"
#include <cmath>
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
template <typename T>
void
cholesky_decomposition (T const* A, int const cols, T* L)
{
    for(int k = 0; k < cols; k++)
    {
        T sum = 0;
        //计算对角元素
        for(int i = 0; i < k; i++)
            sum += L[k*cols+i] * L[k*cols+i];
        sum = A[k*cols+k] - sum;
        L[k*cols+k] = sqrt(sum > 0 ? sum : 0);
        //对角元素以下的同一列元素
        for(int i = k + 1; i < cols; i++)
        {
            sum = 0;
            for(int j = 0; j < k; j++)
                sum += L[i*cols+j] * L[k*cols+j];
            L[i*cols+k] = (A[i*cols+k] - sum) / L[k*cols+k];
        }
        //对角元素以上的同一列元素
        for(int j = 0; j < k; j++)
            L[j*cols+k] = 0;
    }
}

/*
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

}*/
    
MATRIX_NAMESPACE_END
MATH_NAMESPACE_END
#endif //MATH_CHOLESKY_HPP

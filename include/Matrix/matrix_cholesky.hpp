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

template <typename T>
void
cholesky_decomposition(T const* A,int const cols,T* L);





MATRIX_NAMESPACE_END
MATH_NAMESPACE_END
#endif //MATH_CHOLESKY_HPP

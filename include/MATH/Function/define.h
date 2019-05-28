/*
 * 日期:	2019-03-04
 * 时间:	09:01
 * 姓名:	安帅
 * @func    常用命名空间宏定义
*/

#ifndef MATRIX_BASE_DEFINE_H
#define MATRIX_BASE_DEFINE_H

#define FUNCTION_NAMESPACE_BEGIN namespace func {
#define FUNCTION_NAMESPACE_END }

#define MATH_PI         3.14159265358979323846264338327950288   // pi


#define MATH_EPSILON_EQ(x,v,eps) (((v - eps <= x)) && (x <= (v + eps)))
#define MATH_POW2(x) ((x) * (x))
#endif //MATRIX_BASE_DEFINE_H

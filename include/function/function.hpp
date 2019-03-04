/*
 * 日期:	2019-03-04
 * 时间:	08:55
 * 姓名:	安帅
 * @func    常用函数 如 高斯函数等
*/

#ifndef MATRIX_BASE_FUNCTION_HPP
#define MATRIX_BASE_FUNCTION_HPP

#include <cmath>
#include "define.h"

FUNCTION_NAMESPACE_BEGIN
/*
*  @property   高斯函数
*  @func       计算给定高斯函数坐标与标准差的高斯函数值 g(x) = exp( -1/2 * (x/sigma)^2 )
*              峰值为1, 钟形中心为0,钟的宽为sigma
*  @param_in   x                    自变量
*  @param_in   sigma                标准差
*  @return     T
*/
template <typename T>
T
gaussian(T const& x, T const& sigma);

/*
*  @property   高斯函数
*  @func       计算给定高斯函数坐标与方差的高斯函数值 g(x) = exp( -1/2 * (x/sigma)^2 )
*               峰值为1, 钟形中心为0,钟的宽为sigma
*  @param_in   x                    自变量
*  @param_in   sigma2               方差
*  @return     T
*/
template <typename T>
T
gaussian2(T const& x, T const& sigma2);

/*
*  @property   高斯函数
*  @func       计算给定高斯函数坐标与方差的高斯函数值 g(x) = exp( -1/2 * (x/sigma)^2 )
*               峰值为1, 钟形中心为0,钟的宽为sigma
*  @param_in   xx                   自变量x的平方
*  @param_in   sigma                标准差
*  @return     T
*/
template <typename T>
T
gaussian_xx(T const& xx, T const& sigma2);

/*
*  @property   高斯函数
*  @func       计算给定高斯函数坐标与方差的高斯函数值 g(x) = exp( -1/2 * (x/sigma)^2 )
*               峰值为1, 钟形中心为0,钟的宽为sigma
*  @param_in   xx                   自变量x的平方
*  @param_in   sigma2               方差
*  @return     T
*/
template <typename T>
T
gaussian2_xx(T const& xx, T const& sigma2);
FUNCTION_NAMESPACE_END

/********************************************************************
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~函数实现~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
********************************************************************/
FUNCTION_NAMESPACE_BEGIN
template <typename T>
inline T
function::gaussian(T const& x, T const& sigma)
{
    return std::exp(-(x * x) / (T(2) * sigma * sigma));
}

template <typename T>
inline T
function::gaussian2(T const& x, T const& sigma2)
{
    return std::exp(-(x * x) / (T(2) * sigma2));
}

template <typename T>
inline T
function::gaussian_xx(const T &xx, const T &sigma)
{
    return std::exp(-(xx) / (T(2) * sigma * sigma));
}
template <typename T>
inline T
function::gaussian2_xx(const T &xx, const T &sigma2)
{
    return std::exp(-(xx) / (T(2) * sigma2));
}
FUNCTION_NAMESPACE_END

#endif //MATRIX_BASE_FUNCTION_HPP

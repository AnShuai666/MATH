/*
 * 日期:	2018-12-1
 * 时间:	10:12
 * 姓名:	安帅
 * @func    系统相关函数
*/

#ifndef MATH_UTIL_SYSTEM_H
#define MATH_UTIL_SYSTEM_H

#include "define.h"
#include <iostream>
#include <chrono>
#if defined(__linux__)
    #include <endian.h>
    #if __BYTE_ORDER == LITTLE_ENDIAN
        #define HOST_BYTE_ORDER_LITTLE_ENDIAN
    #else
        #define HOST_BYTE_ORDER_BIG_ENDIAN
    #endif
#endif
UTIL_NAMESPACE_BEGIN
SYSTEM_NAMESPACE_BEGIN

/********************************************************************
 *~~~~~~~~~~~~~~~~~~~~~常用系统相关函数声明~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *******************************************************************/

/*
 *  @property   延时函数
 *  @func       延时milli_secs毫秒
 *  @param_in   milli_secs      延时milli_secs毫秒数
*/
void sleep(std::size_t milli_secs);

/*
 *  @property   延时函数
 *  @func       延时secs秒
 *  @param_in   secs      延时secs秒数
*/
void sleep_sec(float secs);

/*
 *  @property   产生随机数
 *  @func       以时间作为随机数种子，产生随机数
 *  @return  int     产生的随机数
*/
int random_int(void);

/*
 *  @property   时间戳打印函数
 *  @func       打印当前程序运行时刻
 *  @param_in   application_name     程序名
*/
void print_build_timestamp(char const* application_name);

/*
 *  @property   时间戳打印函数
 *  @func       实时打印当前程序运行时刻
 *  @param_in   application_name     程序名
 *  @param_in   date     当前程序运行日期
 *  @param_in   time     当前程序运行时刻
*/
void print_build_timestamp(char const* application_name,
        char const* date, char const* time);

/*
 *  @property   段错误函数注册
 *  @func       注册段错误处理函数
*/
void register_segfault_handler();

/*
 *  @property   段错误信号处理函数
 *  @func       处理段错误(SIGSEGV:Segmentation Violation)信号
 *  @param_in   code    信号编号
*/
void signal_segfault_handler(int code);

/*
 *  @property   异常堆栈打印函数
 *  @func       打印出错的栈帧
*/
void print_stack_trace(void);

/*
 *  @property   字节交换函数
 *  @func       按字节交换相邻内存的内容
 *  @param_in   data    待交换的内存
*/
template <int N>
inline void
byte_swap(char* data);

/*
 *  @property   主机字节序转换函数
 *  @func       小端到主机字节序转换
 *  @param_in   x   待转换的内容
*/
template <typename T>
inline T little_end_to_host(T const& x);

/*
 *  @property   主机字节序转换函数
 *  @func       大端到主机字节序转换
 *  @param_in   x   待转换的内容
*/
template <typename T>
inline T big_end_to_host(T const& x);

SYSTEM_NAMESPACE_END
UTIL_NAMESPACE_END

/********************************************************************
 *~~~~~~~~~~~~~~~~~~~~~常用系统相关函数实现~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *******************************************************************/
UTIL_NAMESPACE_BEGIN
SYSTEM_NAMESPACE_BEGIN
template <>
inline void
byte_swap<2>(char *data)
{
    std::swap(data[0],data[1]);
}

template <>
void byte_swap<4>(char *data)
{
    std::swap(data[0],data[3]);
    std::swap(data[1],data[2]);
}

template <>
void byte_swap<8>(char *data)
{
    std::swap(data[0],data[7]);
    std::swap(data[1],data[6]);
    std::swap(data[2],data[5]);
    std::swap(data[3],data[4]);
}

#if defined( HOST_BYTE_ORDER_LITTLE_ENDIAN) && defined(HOST_BYTE_ORDER_BIG_ENDIAN)
#error "不可能同时大端和小端存在！"
#elif defined(HOST_BYTE_ORDER_LITTLE_ENDIAN)

template <typename T>
inline T
little_end_to_host(const T &x)
{
    return x;
}

template <typename T>
inline T
big_end_to_host(const T &x)
{
    T copy(x);
    byte_swap<sizeof(T)>(reinterpret_cast<char*>(&copy));
    return copy;
}

#elif defined(HOST_BYTE_ORDER_BIG_ENDIAN)

template <typename T>
inline T
little_end_to_host(const T &x)
{
    T copy(x);
    byte_swap<sizeof(T)>(reinterpret_cast<char*>(&copy));
    return copy;
}

template <typename T>
inline T
big_end_to_host(const T &x)
{
       return x;
}

#else
#error "不能决定主机的大端小端问题！"
#endif
SYSTEM_NAMESPACE_END
UTIL_NAMESPACE_END
#endif //MATH_UTIL_SYSTEM_H
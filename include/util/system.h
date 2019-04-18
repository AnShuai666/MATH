/*
 * 日期:	2018-12-1
 * 时间:	10:12
 * 姓名:	安帅
 * @func    系统相关函数
*/

#ifndef MATH_SYSTEM_H
#define MATH_SYSTEM_H

#include "define.h"
#include <iostream>

UTIL_NAMESPACE_BEGIN
SYSTEM_NAMESPACE_BEGIN

/********************************************************************
 *~~~~~~~~~~~~~~~~~~~~~常用系统相关函数声明~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *******************************************************************/
void sleep(std::size_t milli_secs);

void sleep_sec(float secs);

int random_int(void);

void print_build_timestamp(char const* application_name);

void print_build_timestamp(char const* application_name,
        char const* date, char const* time);

void register_segfault_handler();

void signal_segfault_handler(int code);

void print_stack_trace(void);

template <int N>
inline void
byte_swap(char* data);

template <typename T>
inline T little_end_to_host(T const& x);

template <typename T>
inline T big_end_to_host(T const& x);

/********************************************************************
 *~~~~~~~~~~~~~~~~~~~~~常用系统相关函数实现~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *******************************************************************/
template <int N>
inline void system::byte_swap(char *data)
{

}

template <>
inline void
system::byte_swap<2>(char *data)
{

}

template <>
void system::byte_swap<4>(char *data)
{

}

template <>
void system::byte_swap<8>(char *data)
{

}

template <typename T>
inline T
system::little_end_to_host(const T &x)
{

}

template <typename T>
inline T
system::big_end_to_host(const T &x)
{

}

SYSTEM_NAMESPACE_END
UTIL_NAMESPACE_END
#endif //MATH_SYSTEM_H
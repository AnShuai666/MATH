/*
 * @desc    常用字符串处理函数
 * @author  安帅
 * @date    2019-01-07
 * @email   1028792866@qq.com
*/

#ifndef UTIL_STRING_H
#define UTIL_STRING_H

#include "define.h"
#include <string>
#include <stdexcept>
#include <sstream>

UTIL_NAMESPACE_BEGIN

/*******************************************************************
*~~~~~~~~~~~~~~~~~~~~~常用字符串处理函数声明~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*******************************************************************/
/*
*  @Number      No.1
*  @property   截取字符串
*  @func       截取字符串左边size个字符
*  @param_in   str         待截取字符串
*  @param_in   size        待截取字符个数
*  @return     std::string
*/
std::string left(std::string const &str,std::size_t size);

/*
*  @Number      No.2
*  @property   截取字符串
*  @func       截取字符串右边size个字符
*  @param_in   str         待截取字符串
*  @param_in   size        待截取字符个数
*  @return     std::string
*/
std::string right(std::string const &str,std::size_t size);

/*
*  @Number      No.3
*  @property   字符小写转换
*  @func       将字符串转换为小写
*  @param_in   str         待转换字符串
*  @return     std::string
*/
std::string lowercase(std::string const &str);

/*
*  @Number      No.4
*  @property   字符大写转换
*  @func       将字符串转换为大写
*  @param_in   str         待转换字符串
*  @return     std::string
*/
std::string uppercase(std::string const &str);

/*
*  @Number      No.5
*  @property   字符串强制转换
*  @func       将字符串强制转换为T类型
*  @param_in   str                   待转换字符串
*  @param_in   strict_conversion      强制转换 默认true
*  @return     T
*/
template <typename T>
T convert(std::string const& str,bool strict_conversion = true);



/*******************************************************************
*~~~~~~~~~~~~~~~~~~~~~常用字符串处理函数实现~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*******************************************************************/
std::string
left(std::string const &str, std::size_t size)
{
    return str.substr(0,size);
}

std::string
right(std::string const &str, std::size_t size)
{
    unsigned long sub_size=str.size() > size?(str.size() - size):0;
    return str.substr(sub_size);
}

std::string
lowercase(std::string const &str)
{
    std::string string(str);
    for (int i = 0; i < str.size(); ++i)
    {
        if(string[i] >= 0x41 && string[i] <= 0x5a)
        {
            string[i] += 0x20;
        }
    }
    return string;
}

std::string
uppercase(std::string const &str)
{
    std::string string(str);
    for (int i = 0; i < str.size(); ++i)
    {
        if(string[i] >= 0x61 && string[i] <= 0x7a)
        {
            string[i] -= 0x20;
        }
    }
    return string;
}

template <typename T>
inline T
convert(std::string const &str, bool strict_conversion)
{
    std::stringstream ss(str);
    T ret = T();
    ss >> ret;
    if (strict_conversion && (!ss.eof() || ss.fail()))
    {
        throw std::invalid_argument("非法字符串转换：" + str);
    }
    return ret;
}

UTIL_NAMESPACE_END

#endif //UTIL_STRING_H

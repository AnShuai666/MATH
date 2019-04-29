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

/*
*  @Number      No.6
*  @property   字符串格式
*  @func       字符串自动换行 每行宽度width时自动换行
*  @param_in   str        待换行字符串
*  @param_in   width      每行显示最多字符个数
*  @return     std::string
*/
std::string word_wrap(char const* str,int width);

/*
*  @Number      No.7
*  @property   字符串格式
*  @func       去掉str末尾所有的\n \r字符 即换行符
*  @param_in   str        待处理字符串
*  @return     void
*/
void clip_newlines(std::string& str);

/*
*  @Number      No.7
*  @property   字符串格式
*  @func       去掉str前端与末尾所有的空格和'\t'字符
*  @param_in   str        待处理字符串
*  @return     void
*/
void clip_whitespaces(std::string& str);

/*
*  @Number      No.8
*  @property   字符串转换
*  @func       将字符串中字符转换为大写，数字保留，其他字符转为空格，多个空格转为1个空格
*  @param_in   str         待转换字符串
*  @return     std::string
*  @Example:   Qcit  Co.,Ltd.  PENTAX Optio330RS
*  ========>   QCIT CO LTD PENTAX OPTIO330RS
*/
std::string uppercase_alpha_numeric_only(std::string const& str);

/*******************************************************************
*~~~~~~~~~~~~~~~~~~~~~常用字符串处理函数实现~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*******************************************************************/

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

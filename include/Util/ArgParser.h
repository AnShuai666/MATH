/*
 * 日期:	2019-4-24
 * 时间:	21:01
 * 姓名:	安帅
 * @func    参数解析
*/

#ifndef MATH_ARGPARSER_H
#define MATH_ARGPARSER_H

#include "Util/define.h"
#include <iostream>
UTIL_NAMESPACE_BEGIN
/********************************************************************
 *~~~~~~~~~~~~~~~~~~~~~文件系统相关函数声明~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *******************************************************************/

class Arguments
{
public:
    Arguments(void);

    void set_usage(std::string const& str);

private:
    std::size_t
};

 UTIL_NAMESPACE_END
#endif //MATH_ARGPARSER_H

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
#include <vector>
UTIL_NAMESPACE_BEGIN

struct ArgOption
{
    char short_option_name;
    std::string long_option_name;
    std::string description;
    bool is_argument_needed;
};

struct ArgResult
{
    ArgOption const* arg_option;
    std::string arg;

    template <typename T>
    T get_arg(void) const;
};
/********************************************************************
 *~~~~~~~~~~~~~~~~~~~~~~~~参数解析类声明~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *******************************************************************/

class Arguments
{
public:
    Arguments(void);

    void set_usage(std::string const& str);

private:
   // std::size_t
   bool auto_exit;
   std::vector<ArgOption> arg_options;
   std::string usage_str;
   std::string description_str;
   int help_text_indent;
   int description_text_width;

   std::vector<ArgResult> arg_results;
   std::size_t current_result;
};

 UTIL_NAMESPACE_END
#endif //MATH_ARGPARSER_H

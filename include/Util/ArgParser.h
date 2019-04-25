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

    void set_usage(char const* argv[0], std::string const& usage);

    void set_description(std::string const& str);

    void set_help_text_indent(int indent);

    void set_nonoption_maxmum(std::size_t limit);

    void set_nonoption_minum(std::size_t limit);

    void set_exit_on_error(bool exit);

    void add_option(char shortname,std::string const& longname,
            bool has_argument,std::string const& description = "");

    void parse(std::vector<std::string> const& args);

    void parse(int argc,char const* const* argv);

private:
   std::size_t nonoption_min;
   std::size_t nonoption_max;
   bool auto_exit;
   std::vector<ArgOption> arg_options;
   std::string usage_str;
   std::string description_str;
   int help_text_indent;
   int description_text_width;

   std::vector<ArgResult> arg_results;
   std::size_t current_result;
};

/********************************************************************
 *~~~~~~~~~~~~~~~~~~~~~~~~参数解析类实现~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *******************************************************************/

template <typename T>
inline T
ArgResult::get_arg(void) const
{
    return ;
}

inline void
Arguments::set_usage(std::string const &str)
{
    this->usage_str = str;
}

 UTIL_NAMESPACE_END
#endif //MATH_ARGPARSER_H

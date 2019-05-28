/*
 * 日期:	2019-4-24
 * 时间:	21:01
 * 姓名:	安帅
 * @func    参数解析
*/

#ifndef MATH_ARGPARSER_H
#define MATH_ARGPARSER_H

#include "../math_define.h"
#include "define.h"
#include "string.h"
#include "exception.h"
#include <iostream>
#include <vector>
MATH_NAMESPACE_BEGIN
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

    void set_usage(char const* argv0, std::string const& usage);

    void set_description(std::string const& str);

    //设置描述语换行宽度
    void set_description_word_warp(int width);

    void set_help_text_indent(int indent);

    void set_nonoption_max_number(std::size_t limit_min);

    void set_nonoption_min_number(std::size_t limit_max);

    void set_exit_on_error(bool exit);

    void add_option(char shortname,std::string const& longname,
            bool has_argument,std::string const& description = "");

    //只抛出util::Exception类型异常
    void parse(std::vector<std::string> const& args)
    throw(util::Exception);

    //只抛出util::Exception类型异常
    void parse(int argc,char const* const* argv)
    throw(util::Exception);

    void generate_help_text(std::ostream& ostream) const;

private:
    void parse_long_option(std::string const& token);
    bool parse_short_option(std::string const& token1, std::string const& token2);
    ArgOption const* find_option(char short_option_name);
    ArgOption const* find_option(std::string const& long_option_name);

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
   std::string command_name;

   std::size_t current_result;
};

/********************************************************************
 *~~~~~~~~~~~~~~~~~~~~~~~~参数解析类实现~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *******************************************************************/

template <typename T>
inline T
ArgResult::get_arg(void) const
{
    return util::convert<T>(this->arg);
}

inline void
Arguments::set_usage(std::string const &str)
{
    this->usage_str = str;
}

inline void
Arguments::set_description(std::string const &str)
{
    this->description_str = str;
}

inline void
Arguments::set_description_word_warp(int width)
{
    this->description_text_width = width;
}

inline void
Arguments::set_help_text_indent(int indent)
{
    this->help_text_indent = indent;
}

inline void
Arguments::set_nonoption_min_number(std::size_t limit_min)
{
    this->nonoption_min = limit_min;
}

inline void
Arguments::set_nonoption_max_number(std::size_t limit_max)
{
    this->nonoption_max = limit_max;
}

inline void
Arguments::set_exit_on_error(bool exit)
{
    this->auto_exit = exit;
}

 UTIL_NAMESPACE_END
 MATH_NAMESPACE_END
#endif //MATH_ARGPARSER_H

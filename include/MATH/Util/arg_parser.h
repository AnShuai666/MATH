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
    T getArg(void) const;
};
/********************************************************************
 *~~~~~~~~~~~~~~~~~~~~~~~~参数解析类声明~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *******************************************************************/

class Arguments
{
public:
    Arguments(void);

    void setUsage(std::string const& str);

    void setUsage(char const* argv0, std::string const& usage);

    void setDescription(std::string const& str);

    //设置描述语换行宽度
    void setDescriptionWordWarp(int width);

    void setHelpTextIndent(int indent);

    void setNonoptionMaxNumber(std::size_t limit_min);

    void setNonoptionMinNumber(std::size_t limit_max);

    void setExitOnError(bool exit);

    void addOption(char shortname,std::string const& longname,
            bool has_argument,std::string const& description = "");

    //只抛出util::Exception类型异常
    void parse(std::vector<std::string> const& args)
    throw(util::Exception);

    //只抛出util::Exception类型异常
    void parse(int argc,char const* const* argv)
    throw(util::Exception);

    void generateHelpText(std::ostream& ostream) const;

private:
    void parseLongOption(std::string const& token);
    bool parseShortOption(std::string const& token1, std::string const& token2);
    ArgOption const* findOption(char short_option_name);
    ArgOption const* findOption(std::string const& long_option_name);

private:
   std::size_t _nonoption_min;
   std::size_t _nonoption_max;
   bool _auto_exit;
   std::vector<ArgOption> _arg_options;
   std::string _usage_str;
   std::string _description_str;
   int _help_text_indent;
   int _description_text_width;

   std::vector<ArgResult> _arg_results;
   std::string _command_name;

   std::size_t _current_result;
};

/********************************************************************
 *~~~~~~~~~~~~~~~~~~~~~~~~参数解析类实现~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *******************************************************************/

template <typename T>
inline T
ArgResult::getArg(void) const
{
    return util::convert<T>(this->arg);
}

inline void
Arguments::setUsage(std::string const &str)
{
    this->_usage_str = str;
}

inline void
Arguments::setDescription(std::string const &str)
{
    this->_description_str = str;
}

inline void
Arguments::setDescriptionWordWarp(int width)
{
    this->_description_text_width = width;
}

inline void
Arguments::setHelpTextIndent(int indent)
{
    this->_help_text_indent = indent;
}

inline void
Arguments::setNonoptionMinNumber(std::size_t limit_min)
{
    this->_nonoption_min = limit_min;
}

inline void
Arguments::setNonoptionMaxNumber(std::size_t limit_max)
{
    this->_nonoption_max = limit_max;
}

inline void
Arguments::setExitOnError(bool exit)
{
    this->_auto_exit = exit;
}

 UTIL_NAMESPACE_END
 MATH_NAMESPACE_END
#endif //MATH_ARGPARSER_H

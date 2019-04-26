/*
 * 日期:	2019-4-24
 * 时间:	21:01
 * 姓名:	安帅
 * @func    参数解析
*/

#include "Util/ArgParser.h"
#include "Util/string.h"
#include <limits>
#include <iomanip>

UTIL_NAMESPACE_BEGIN
/********************************************************************
 *~~~~~~~~~~~~~~~~~~~~~~~~参数解析类实现~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *******************************************************************/
Arguments::Arguments(void)
    :nonoption_min(0)
    ,nonoption_max(std::numeric_limits<std::size_t>::max())
    ,auto_exit(false)
    ,help_text_indent(16)
    ,description_text_width(75)
    ,current_result(std::numeric_limits<std::size_t>::max())
{
}

void
Arguments::set_usage(const char *argv0, std::string const &usage)
{
    std::stringstream ss;
    ss << "Usage: " << argv0 <<" " << usage;
    this->usage_str = ss.str();
}

void
Arguments::add_option(char shortname, std::string const &longname, bool has_argument,
                           const std::string &description)
{
    if(shortname == '\0' && longname.empty())
        throw std::invalid_argument("长短参数都未给定");

    //检测参数选项是否存在
    for (std::size_t i = 0; i < this->arg_options.size(); ++i)
    {
        if ((shortname != '\0' && this->arg_options[i].short_option_name == shortname)
            || (!longname.empty() && this->arg_options[i].long_option_name == longname))
            throw std::runtime_error("参数选项已经存在！");
    }

    ArgOption argOption;
    argOption.short_option_name = shortname;
    argOption.long_option_name = longname;
    argOption.description = description;
    argOption.is_argument_needed = has_argument;
    this->arg_options.push_back(argOption);
}

void
Arguments::parse(std::vector<std::string> const &args)
throw(util::Exception)
{
    try
    {
        this->arg_results.clear();
        this->command_name.clear();
        this->current_result = std::numeric_limits<std::size_t>::max();

        bool parse_option = true;
        for (std::size_t i = 0; i < args.size(); ++i)
        {
            if (i == 0)
            {
                this->command_name = args[i];
                continue;
            }

            std::string token = args[i];
            util::clip_newlines(token);
            util::clip_whitespaces(token);

            if (token.empty())
                continue;

            if (parse_option && token.size() == 2 && token == "--")
            {
                parse_option = false;
                continue;
            }
            else if (parse_option && token.size() >= 3 && token[0] == '-' && token[1] == '-')
            {
                this->parse_long_option(token);
            }
            else if (parse_option && token.size() >= 2 && token[0] == '-')
            {
                std::string next_token;
                if (i + 1 < args.size())
                {
                    next_token = args[i + 1];
                    util::clip_newlines(next_token);
                    util::clip_whitespaces(next_token);
                }
                bool used_next = this->parse_short_option(token,next_token);
                if (used_next)
                    i += 1;
            }
            else
            {
                ArgResult argResult;
                argResult.arg_option = nullptr;
                argResult.arg = token;
                this->arg_results.push_back(argResult);
            }
        }

        std::size_t num_no_option = 0;
        for (std::size_t j = 0; j < this->arg_results.size(); ++j)
        {
            if(this->arg_results[j].arg_option == nullptr)
                num_no_option += 1;
        }

        if (num_no_option > this->nonoption_max)
            throw util::Exception("无参数选项参数过多");
        if (num_no_option < this->nonoption_min)
            throw util::Exception("无参数选项参数过少");
    }
    catch(util::Exception const& e)
    {
        if (!this->auto_exit)
            throw;
        std::cerr << std::endl;
        this->generate_help_text(std::cerr);
        std::cerr << std::endl << "错误：" << e.what() << std::endl;
        std::exit(1);
    }
}

void
Arguments::parse(int argc, char const *const *argv)
throw(util::Exception)
{
    std::vector<std::string> args;
    for (int i = 0; i < argc; ++i)
    {
        args.push_back(argv[i]);
    }
    this->parse(args);
}

void
Arguments::generate_help_text(std::ostream &ostream) const
{
    std::string decsription = util::word_wrap(
            this->description_str.c_str(),this->description_text_width);

    if (!decsription.empty())
        ostream << decsription << std::endl << std::endl;

    if (!this->usage_str.empty())
        ostream << this->usage_str << std::endl;

    if (!this->arg_options.empty() && (!this->usage_str.empty() || !decsription.empty()))
        ostream << "可用的参数选项为：" << std::endl;

    for (size_t i = 0; i < this->arg_options.size(); ++i)
    {
        ArgOption const& argOption(this->arg_options[i]);
        std::stringstream option_string;

        if (argOption.short_option_name != '\0')
        {
            option_string << "-" << argOption.short_option_name;
            if (argOption.is_argument_needed && argOption.long_option_name.empty())
                option_string << " ARG";
            if (!argOption.long_option_name.empty())
                option_string << ", ";
        }

        if (!argOption.long_option_name.empty())
        {
            option_string << "--" << argOption.long_option_name;
            if (argOption.is_argument_needed)
                option_string << "=ARG";
        }
        option_string << " ";
        ostream << " "
                << std::setiosflags(std::ios::left)
                << std::setw(this->help_text_indent)
                << option_string.str()
                << argOption.description
                << std::endl;
    }

}

void
Arguments::parse_long_option(std::string const &token)
{
    std::size_t position = token.find_first_of('=');
    std::string option = token.substr(2,position - 2);//”--“与"="的参数名 --help = "ss"
    std::string arg;
    if (position != std::string::npos)
        arg = token.substr(position + 1);// “="之后的参数
    if (option.empty())
        throw util::Exception("非法的参数名选项： ",token);

    ArgOption const* argOption = this->find_option(option);
    if (argOption == nullptr)
        throw util::Exception("非法的参数名选项：",token);

    if (argOption->is_argument_needed && arg.empty())
        throw util::Exception("参数名选项缺少参数",token);

    ArgResult argResult;
    argResult.arg = arg;
    argResult.arg_option = argOption;
    this->arg_results.push_back(argResult);
}

bool
Arguments::parse_short_option(std::string const &token1, std::string const &token2)
{
    if (token1.size() < 2)
        throw std::runtime_error("短参数选项字符过少");

    char option = token1[1];
    std::string arg;
    bool retval = false;
    ArgOption const* argOption = this->find_option(option);

    if (argOption == nullptr)
        throw util::Exception("非法的参数选项：",token1);

    if (!argOption->is_argument_needed && token1.size() > 2)
    {
        for (int i = 0; i < token1.size(); ++i)
        {
            std::string short_option = "-";
            short_option.append(1,token1[i]);
            this->parse_short_option(short_option,"");
        }
        return false;
    }

    if (argOption->is_argument_needed && token1.size() == 2)
    {
        if (token2.empty() || token2[0] == 2)
            throw util::Exception("参数选项缺少参数： ",token1);
        arg = token2;
        retval = true;
    }
    else if (argOption->is_argument_needed)
    {
        arg = token1.substr(2);
    }

    if (!argOption->is_argument_needed && token1.size() != 2)
        throw util::Exception("参数选项未预期的参数： ",token1);

    ArgResult argResult;
    argResult.arg = arg;
    argResult.arg_option = argOption;
    this->arg_results.push_back(argResult);

    return retval;
}

ArgOption const*
Arguments::find_option(char short_option_name)//TODO:改写成引用形式 提高效率
{
    for (std::size_t i = 0; i < this->arg_options.size(); ++i)
    {
        if(this->arg_options[i].short_option_name == short_option_name)
            return &this->arg_options[i];
    }
    return nullptr;
}

ArgOption const*
Arguments::find_option(std::string const &long_option_name)
{
    for (std::size_t i = 0; i < this->arg_options.size(); ++i)
    {
        if(this->arg_options[i].long_option_name == long_option_name)
            return &this->arg_options[i];
    }
    return nullptr;
}
UTIL_NAMESPACE_END
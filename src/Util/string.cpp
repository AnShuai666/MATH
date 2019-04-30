/*
 * 日期:	2019-4-24
 * 时间:	21:01
 * 姓名:	安帅
 * @func    参数解析
*/

#include "Util/string.h"
UTIL_NAMESPACE_BEGIN
/********************************************************************
 *~~~~~~~~~~~~~~~~~~~~~~~~常用字符串处理函数实现~~~~~~~~~~~~~~~~~~~~~~~~
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


std::string
word_wrap(char const *str, int width)
{
    if (str == nullptr)
        return std::string();
    if (width <= 0)
        return str;

    int spaceleft = width;
    bool firstword = true;
    std::string out;

    for (int i = 0,word = 0; true ; ++i)
    {
        char c(str[i]);
        bool softbreak = (c == ' ' || c == '\t' || c == '\0' || c == '\n');

        if (softbreak)
        {
            if (word > spaceleft)
            {
                if(!firstword)
                    out.append(1,'\n');
                spaceleft = width - word - 1;
            }
            else
            {
                if (!firstword)
                    out.append(1,' ');
                out.append(str + i - word,word);
                spaceleft -= word + 1;
            }
            firstword = false;

            word = 0;
            if (c == '\n')
            {
                out.append(1,'\n');
                firstword = true;
                word = 0;
                spaceleft = width;
            }
        }
        else
        {
            word += 1;
        }

        if (str[i] == '\0')
            break;
    }
    return out;
}

void clip_newlines(std::string &str)
{
    while (!str.empty() && (*str.rbegin() == '\r'
        || *str.rbegin() == '\n'))
        str.resize(str.size() - 1);
}

void
clip_whitespaces(std::string &str)
{
    while (!str.empty() && (str.back() == ' ' || str.back() == '\t'))
        str.resize(str.size() - 1);
    while (!str.empty() && (str.front() == ' ' || str.front() == '\t'))
        str.erase(str.front());
}

std::string
uppercase_alpha_numeric_only(std::string const &str)
{
    std::string ret;

    bool was_alpha_numeric = true;
    for (int i = 0; i < str.size(); ++i)
    {
        if(std::isalnum(str[i]))
        {
            if (!was_alpha_numeric)
                ret.append(1,' ');//在当前ret末尾添加‘ ’
             ret.append(1,std::toupper(str[i]));
             was_alpha_numeric = true;
        }
        else
            was_alpha_numeric = false;
    }
    return ret;
}

UTIL_NAMESPACE_END
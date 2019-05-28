/*
 * @desc    时间定义
 * @author  安帅
 * @date    2019-04-26
 * @email   1028792866@qq.com
*/

#ifndef MATH_TOKENIZER_H
#define MATH_TOKENIZER_H

#include <vector>
#include <string>
#include <sstream>
#include "define.h"
UTIL_NAMESPACE_BEGIN
//存储的是令牌数
class Tokenizer : public std::vector<std::string>
{
public:
    void split(std::string const& str, char delim = ' ',
            bool keep_empty = false);

    void parse_cmd(std::string const& str);

    //用空格将各个令牌连接 起始位置position,连接num个令牌
    std::string concatenate(std::size_t position, std::size_t num = 0)const;

    template <typename T>
    T get_as(std::size_t position) const;
};

inline void
Tokenizer::split(std::string const &str, char delim, bool keep_empty)
{
    this->clear();
    std::size_t new_token = 0;

    for (std::size_t current_position = 0; current_position < str.size();++current_position)
    {
        if(str[current_position] == delim)
        {
            //获得两delim（字符分隔符）之间的字符串 存于令牌中
            std::string token = str.substr(new_token,current_position - new_token);
            if (keep_empty || !token.empty())
                this->push_back(token);
            new_token = current_position + 1;
        }
    }

    if (keep_empty || new_token < str.size())
        //获得最后一个delim之后的字符串
        this->push_back(str.substr(new_token));
}

inline std::string
Tokenizer::concatenate(std::size_t position, size_t num) const
{
    std::stringstream ss;
    std::size_t max = (num == 0 ? this->size() : std::min(position + num, this->size()));

    for (std::size_t i = position; i < max; ++i)
    {
        ss << (i == position ? "" : " ");
        ss << this->at(i);
    }

    return ss.str();
}
UTIL_NAMESPACE_END
#endif //MATH_TOKENIZER_H

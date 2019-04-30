/*
 * 日期:	2019-4-25
 * 时间:	10:06
 * 姓名:	安帅
 * @func    字符串文件函数测试
*/

#include <iostream>
#include "Util/string.h"

int main()
{

    //No.5convert函数 强制转换为int类型
    std::cout<<"test convert()"<<std::endl;
    std::string str = "12345";
    int integer = util::convert<int>(str, false);
    std::cout<<integer<<std::endl;

    //No.6word_wrap函数 自动换行
    std::cout<<"test word_wrap()"<<std::endl;

    str = "1234567891 011\t13\t    \t\r\n";
    std::cout << str << std::endl;
    std::cout<<util::word_wrap(str.c_str(),5)<<std::endl;

    //No.7clip_newlines函数 去掉末尾newlines '\r'--回车,'\n'--换行
    //unix 换行是\n Mac:\r Windows:\n\r
    std::cout<<"test clip_newlines()"<<std::endl;
    util::clip_newlines(str);
    std::cout<<str;

    //No.8clip_whitespaces函数 去掉str最前最后的空格和\t
    //str = "\t1234567891 011\t13\t";
    std::cout<<"test clip_whitespaces()"<<std::endl;
    util::clip_whitespaces(str);
    std::cout<<str<<std::endl;

    //No.9
    str = "Asahi Optical Co.,Ltd.  PENTAX Optio330RS";
    std::cout<<"test uppercase_alpha_numeric_only"<<std::endl;
    util::uppercase_alpha_numeric_only(str);
    std::cout<<str<<std::endl;
    str = "Canon IXUS";
    util::uppercase_alpha_numeric_only(str);

    std::cout<<str<<std::endl;

    return 0;
}

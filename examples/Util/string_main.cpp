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
    std::string str = "12345";
    int integer = util::convert<int>(str, false);
    std::cout<<integer<<std::endl;

    //No.6word_wrap函数 自动换行
    str = "123456789101112";
    std::cout<<util::word_wrap(str.c_str(),5)<<std::endl;
    return 0;
}

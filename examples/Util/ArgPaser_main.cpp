/*
 * 日期:	2019-4-25
 * 时间:	11:08
 * 姓名:	安帅
 * @func    文件系统命令行参数解析函数测试
*/

#include <iostream>
#include "Util/ArgParser.h"
using namespace math;
int main(int argc,char** argv)
{
    //struct ArgOption

    //struct ArgResult
    util::ArgResult argResult;
    argResult.arg = argv[1];
    std::cout<<argResult.get_arg<int>()<<std::endl;

    //class Arguments
    util::Arguments arguments;
    arguments.set_usage("usage");


    return 0;
}
/*
 * 日期:	2019-4-24
 * 时间:	21:01
 * 姓名:	安帅
 * @func    日志记录文件函数测试
*/

#include <iostream>
#include "Util/logging.h"

int main()
{
    util::Logging logging(util::Logging::LOG_DEBUG);
    logging.info()<<"info"<<std::endl;
    logging.error()<<"error"<<std::endl;
    logging.warning()<<"warning"<<std::endl;
    logging.debug()<<"debug"<<std::endl;
    logging.verbose()<<"verbose"<<std::endl;
    std::cerr<<"cerr"<<std::endl;
    return 0;
};
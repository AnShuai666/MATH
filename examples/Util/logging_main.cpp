//
// Created by yhl on 19-4-24.
//

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
/*
 * 日期:	2018-12-1
 * 时间:	10:12
 * 姓名:	安帅
 * @func   系统相关函数
*/
#include "Util/system.h"
#include <thread>
#include <csignal>
#include <execinfo.h>
MATH_NAMESPACE_BEGIN
UTIL_NAMESPACE_BEGIN
SYSTEM_NAMESPACE_BEGIN

/********************************************************************
 *~~~~~~~~~~~~~~~~~~~~~常用系统相关函数实现~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *******************************************************************/

void
sleep(std::size_t milli_secs)
{
    std::this_thread::sleep_for(std::chrono::milliseconds(milli_secs));
}

void
sleep_sec(float secs)
{
    util_system::sleep((std::size_t)(secs*1000));
}

int
random_int()
{
    std::srand(std::time(nullptr));
}

void
print_build_timestamp(char const *application_name)
{
    print_build_timestamp(application_name,__DATE__,__TIME__);
}

void
print_build_timestamp(char const *application_name,
        char const *date, char const *time)
{
    std::cout << application_name << "(编译于 " << date <<", "
              << time << ".)" <<std::endl;
}

void register_segfault_handler()
{
    std::signal(SIGSEGV,util_system::signal_segfault_handler);
}

void
signal_segfault_handler(int code)
{
    if (code != SIGSEGV)
    {
        return;
    }
    std::cerr << "接收到信号SIGSEGV(段错误)" << std::endl;
    print_stack_trace();
}

void
print_stack_trace()
{
    void *array[32];
    //::是域运算符
    //域运算符一般用来选用全局的函数
    int const size = ::backtrace(array,32);

    std::cerr << "获取了 " <<size << "　个栈帧：　";
    for (int i = 0; i < size; ++i)
    {
        std::cerr << " " << array[i];
    }
    std::cerr << std::endl;

    std::cerr << "段错误！" << std::endl;
    ::exit(1);
}

SYSTEM_NAMESPACE_END
UTIL_NAMESPACE_END
MATH_NAMESPACE_END
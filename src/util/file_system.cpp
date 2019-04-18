/*
 * 日期:	2018-12-1
 * 时间:	10:12
 * 姓名:	安帅
 * @func    文件系统
*/

#include "util/file_system.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <cerrno>
#include <cstdio>
#include <pwd.h>
#include <cstring>
#ifndef  PATH_MAX
#define PATH_MAX 2048
#endif

UTIL_NAMESPACE_BEGIN

char home_path[PATH_MAX] = { 0 };

bool
file_system::is_directory_exist(char const *pathname)
{
    struct stat statebuf;
    if(::stat(pathname,&statebuf) < 0)
    {
        std::perror("stat");
        return false;
    }

    if (!S_ISDIR(statebuf.st_mode))
    {
        std::perror("S_ISDIR");
        return false;
    }

    return true;
}

bool
file_system::is_file_exists(char const *pathname)
{
#ifdef  _WIN32
    struct _stat statbuf;
    if(::_stat(pathname,&statbuf) < 0)
        {
        return false;
        }

    if(!(statbuf.st_mode & _S_IFREG)
    {
        return false;
    }
#else
    struct stat statbuf;
    if(::stat(pathname,&statbuf) < 0)
    {
        std::perror("stat");
        return false;
    }

    if (!S_ISREG(statbuf.st_mode))
    {
        std::perror("S_ISREG");
        return false;
    }

    return true;
#endif
}


char const*
file_system::get_home_dir(void)
{
    if (*home_path != 0)
    {
        return home_path;
    }

    //geteuid()用来取得执行目前进程有效的用户识别码.
    uid_t user_id = ::geteuid();
    //getpwuid()用来逐一搜索参数uid 指定的用户识别码, 找到时便将该用户的数据以结构返回
    struct passwd* user_info = ::getpwuid(user_id);
    if (user_info == nullptr || user_info->pw_dir == nullptr)
    {
        //TODO:抛出异常
    }
    std::strncpy(home_path,user_info->pw_dir,PATH_MAX);

    return home_path;
}


UTIL_NAMESPACE_END
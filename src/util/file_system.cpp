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
#include <iostream>
#include <dirent.h>
#include <fstream>

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
file_system:: is_directory_empty(char const* pathname)
{
    DIR *dir = opendir(pathname);
    struct dirent *ent=NULL;
    while (ent = readdir (dir))
    {
        if ((strcmp(".", ent->d_name)==0) || (strcmp("..", ent->d_name)==0))
        {
            continue;
        }
        if ((ent->d_type == 4) || (ent->d_type == 8))
        {
            return false;
        }
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

char*
file_system::get_cwd(char *buf, std::size_t size)
{
    return ::getcwd(buf,size);
}

bool
file_system::set_cwd(char const *pathname)
{
    return ::chdir(pathname) >= 0;
}

bool
file_system::mkdir(char const *pathname)
{
    if(is_directory_exist(pathname))
    {
        std::cerr<<"文件夹已存在！"<<std::endl;
        return false;
    }
    //111 | 040 | 010 = 750权限
    return ::mkdir(pathname,S_IRWXU | S_IRGRP | S_IXGRP) >= 0;
}
bool
file_system:: rmdir(char const* pathname)
{
    if(!is_directory_exist(pathname))
    {
        std::cerr<<"文件夹不存在！"<<std::endl;
        return false;
    }
    else if(is_directory_empty(pathname))
        return ::rmdir(pathname) >=0;
    else
    {
        std::cerr<<"文件夹内不为空，不能删除！"<<std::endl;
    }

}
bool
file_system:: unlink(char const* pathname)
{
    if(is_file_exists(pathname))
        return ::unlink(pathname);
    else
    {
        std::cerr<<pathname<<":该文件不存在"<<std::endl;
        return false;
    }
}
bool
file_system:: rename(char const* from, char const* to)
{
    if(is_file_exists(from))
        return ::rename(from,to);
    else
    {
        std::cerr<<from<<":该文件不存在"<<std::endl;
        return false;
    }
}
void
file_system:: copy_file(char const* src, char const* dst,int type)
{
    if(1==type)
    {
        std::ifstream in(src);
        std::ofstream out(dst);

        if (!in&&!out)
        {
            std::cerr << "文件打开失败！" << std::endl;
            return ;
        }
        std::string str;
        while (!in.eof())
        {
            getline(in,str);
            out <<str<<"\n";
        }
        out << std::endl;
        out.close();
        in.close();
    }
    else
    {
        std::ifstream in;
        std::ofstream out;
        in.open(src, std::ios::binary|std::ios::in|std::ios::ate);//直接跳到末尾，方便预留空间。
        out.open(dst, std::ios::binary|std::ios::out);

        if (!in&&!out)
        {
            std::cerr << "文件打开失败！" << std::endl;
            return ;
        }
        int length = in.tellg();
        char* data = new char[length];
        in.seekg(0);
        in.read(data,length);
        out.write(data,length);

        out.close();
        in.close();

        delete data;
    }



}
UTIL_NAMESPACE_END
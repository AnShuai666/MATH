/*
 * 日期:	2018-12-1
 * 时间:	10:12
 * 姓名:	安帅
 * @func    文件系统
*/

#include "Util/file_system.h"
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
#include <bits/locale_facets.tcc>
#include <algorithm>

#ifndef  PATH_MAX
#define PATH_MAX 2048
#endif
MATH_NAMESPACE_BEGIN
UTIL_NAMESPACE_BEGIN
/********************************************************************
 *~~~~~~~~~~~~~~~~~~~~~文件系统相关函数实现~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *******************************************************************/
char home_path[PATH_MAX] = { 0 };

bool
is_directory_exist(char const *pathname)
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
 is_directory_empty(char const* pathname)
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
is_file_exists(char const *pathname)
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
get_home_dir(void)
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
get_cwd(char *buf, std::size_t size)
{
    return ::getcwd(buf,size);
}

bool
set_cwd(char const *pathname)
{
    return ::chdir(pathname) >= 0;
}

bool
mkdir(char const *pathname)
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
 rmdir(char const* pathname)
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
 unlink(char const* pathname)
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
 rename(char const* from, char const* to)
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
copy_file(char const* src, char const* dst,int type)
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

void
read_file_to_string(std::string const &filename, std::string &data)
{
    std::ifstream in(filename.c_str(),std::ios::binary);
    //in.open(filename);//,std::ios::binary);
    if (!in.good())
    {
        //TODO:抛出异常
        return;
    }

    //基地址为文件结束处，偏移地址为0，于是指针定位在文件结束处
    in.seekg(0,std::ios::end);
    //tellg（）函数不需要带参数，它返回当前定位指针的位置，也代表着输入流的大小。
    std::size_t length = in.tellg();
    in.seekg(0,std::ios::beg);
    data.resize(length);
    //read()从文件中读取 length 个字符到 data指向的缓存中
    in.read(const_cast<char*>(data.c_str()),length);
    in.close();
}

void
write_string_to_file(std::string const &data, std::string const &filename)
{
    std::ofstream out(filename.c_str(),std::ios::binary);
    if (!out.good())
    {
        //抛出异常
    }
    out.write(data.c_str(),data.size());
    out.close();
}

std::string
get_cwd_string(void)
{
    std::size_t size = 1 << 8;
    while (true)
    {
        char* buf = new char[size];
        if (get_cwd(buf,size) == buf)
        {
            std::string ret(buf);
            delete[] buf;
            return ret;
        }
        delete[] buf;
        size = size << 1;
        if (size > (1 << 15))
            //TODO:抛出异常,代替exit
            exit(0);
    }
}

std::string
get_binary_path()
{
    char path[PATH_MAX];
    std::fill(path,path+PATH_MAX,'\0');
#if defined(_WIN32)
    //TODO:WINDOWS OS
#elif defined(__APPLE__)
    //TODO:APPLE OS
#elif defined(__linux__)
    //  readlink  执行成功则 传符号连接所指的文件路径字符串，
    //          失败返回-1， 错误代码存于errno
    //  /proc/self/exe 代表当前程序
    // 可以用readlink读取它的源路径就可以获取当前程序的绝对路径
    ssize_t n_chars = ::readlink("/proc/self/exe",path,PATH_MAX);
#else
    #error "不能获取当前二进制路径：操作系统不支持！"
#endif

if (n_chars >= PATH_MAX)
    //TODO:抛出异常
    throw "缓存区太小";
return std::string(path);
}

bool
is_absolute_path(std::string const &path)
{
#ifdef _WIN32
    //TODO:WINDOWS OS
#else
    return path.size() >= 1 && path[0] == '/';
#endif
}

std::string sanitize_path(std::string const &path)
{
    if (path.empty())
        return "";
    std::string result = path;
    //用sash/代替backslash'\\'
    std::replace(result.begin(),result.end(),'\\','/');

    //去除双斜杠//->/ erase(pos,n); 删除从pos开始的n个字符
    for(std::size_t i = 0;i<result.size()-1;)
    {
        if (result[i] == '/' && result[i+1] == '/')
        {
            result.erase(i,1);
        }
        else
        {
            i += 1;
        }
    }
    if (result.size() > 1 && result[result.size() - 1] == '/')
        result.erase(result.end() - 1);
    return result;
}

std::string join_path(std::string const &path1, std::string const &path2)
{
    std::string p2 = sanitize_path(path2);
    if (is_absolute_path(p2))
    {
        return p2;
    }

#if defined(_WIN32)
    //TODO:WINDOWS OS
#elif defined(linux)
    return sanitize_path(path1) + '/' + p2;
#else
    #error "当前操作系统目前不支持"
#endif
}

std::string
get_absolute_path(std::string const &path)
{
    return join_path(get_cwd_string(),path);
}

std::string
get_directory_name(std::string const &path)
{
    if (path.empty())
    {
        return ".";
    }
    std::size_t length = path.size();
    //跳过path最后的slash/
    while (length >0 && path[length - 1] == '/')
    {
        length -= -1;
    }
    if (length == 0)
    {
        return "/";
    }

    //跳过文件名部分
    while (length > 0 && path[length - 1] != '/')
    {
        length -= 1;
    }
    if (length == 0)
    {
        return ".";
    }

    //跳过去除文件名部分后的slash'/'
    while (length > 1 && path[length - 1] == '/')
    {
        length -= 1;
    }

    return path.substr(0,length);
}

std::string
basename(std::string const &path)
{
    //跳过末尾的斜杠/
    std::size_t length = path.size();
    while (length > 0 && path[length - 1] == '/')
    {
        length -= 1;
    }
    if (length == 0)
    {
        return "";
    }

    //跳过文件名部分
    std::size_t base = length - 1;
    while (base > 0 && path[base - 1] != '/')
    {
        base -= 1;
    }
    return path.substr(base,length - base);
}

std::string
replace_extension(std::string const &file, std::string const &extension)
{
    std::size_t slash_position = file.find_last_of('/');
    if (slash_position == std::string::npos)
    {
        slash_position = 0;
    }

    std::size_t dot_position = file.find_last_of('.');
    if (dot_position == std::string::npos || dot_position < slash_position)
    {
        return file + "." + extension;
    }
    return file.substr(0,dot_position) + "." + extension;
}

std::string
File::get_absolute_name(void) const
{
#ifdef _WIN32
#else
    return (!path.empty() && *path.rbegin() == '/'
    ? path + name
    : path + "/" + name);
#endif
}

bool
File::operator<(const File &rhs) const
{
    if (this->is_directory && !rhs.is_directory)
    {
        return true;
    }
    else if(!this->is_directory && rhs.is_directory)
    {
        return false;
    }
    else if (this->path < rhs.path)
    {
        return true;
    }
    else
    {
        return (this->name < rhs.name);
    }
}

void
Directory::scan(std::string const &path)
{
    this->clear();
#if defined(_WIN32)

#elif defined(linux)
    DIR *dir = ::opendir(path.c_str());
    if (dir == nullptr)
        //TODO:为定位异常信息，重写加上错误信息std::strerror(errno) 或perror
        throw "不能打开文件夹目录：" ;
    //不但指向文件目录，也指向目录中文件
    dirent *dirent;
    while ((dirent = ::readdir(dir)))
    {
        //strcmp
        //如果返回值 < 0，则表示 str1 小于 str2。
        //如果返回值 > 0，则表示 str2 小于 str1。
        //如果返回值 = 0，则表示 str1 等于 str2。
        if (!std::strcmp(dirent->d_name,"."))
            continue;
        if (!std::strcmp(dirent->d_name,".."))
            continue;
        this->push_back(File());
        this->back().path = path;
        this->back().name = dirent->d_name;
        this->back().is_directory = (dirent->d_type == DT_DIR);
    }
    ::closedir(dir);
#endif
}
UTIL_NAMESPACE_END
MATH_NAMESPACE_END
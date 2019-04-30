/*
 * 日期:	2018-12-1
 * 时间:	10:12
 * 姓名:	安帅
 * @func    文件系统
*/

#ifndef MATH_FILE_SYSTEM_H
#define MATH_FILE_SYSTEM_H
#include <string>
#include <vector>
#include "define.h"

UTIL_NAMESPACE_BEGIN
FILE_SYSTEM_NAMESPACE_BEGIN
/********************************************************************
 *~~~~~~~~~~~~~~~~~~~~~文件系统相关函数声明~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *******************************************************************/

/********************************************************************
 *~~~~~~~~~~~~~~~~~~~~~文件系统路径相关操作~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *******************************************************************/
/*
 *  @property   文件夹检测函数
 *  @func       检测文件夹是否存在
 *  @param_in   pathname        路径名
 *  @return     bool
 *              存在             true
 *              不存在           false   errno被设置
*/
bool is_directory_exist(char const* pathname);
/*
 *  @property   文件夹检测函数
 *  @func       检测文件夹是否为空
 *  @param_in   pathname        路径名
 *  @return     bool
 *              存在             true
 *              不存在           false   errno被设置
*/
bool is_directory_empty(char const* pathname);
/*
 *  @property   文件检测函数
 *  @func       检测文件是否存在
 *  @param_in   pathname        路径名
 *  @return     bool
 *              存在             true
 *              不存在           false   errno被设置
*/
bool is_file_exists(char const* pathname);

/*
 *  @property   用户目录获取
 *  @func       获取当前进程用户目录/home/user
 *  @return     char const*     用户目录
*/
char const* get_home_dir(void);

/*
 *  @property   当前进程目录获取
 *  @func       获取当前进程(可执行程序)运行目录的绝对路径pwd
 *  param_in    buf  getcwd()会将当前工作目录的绝对路径复制到参数buffer所指的内存空间中
 *  param_in    size    buffer的空间大小
 *  @return     char const*     当前进程绝对路径
 *  @example    char buf[MAXPATH];
                get_cwd(buf,MAXPATH);
*/
char* get_cwd(char* buf,std::size_t size);

/*
 *  @property   改变当前进程目录
 *  @func       改变当前进程目录 绝对路径
 *  @param_in   pathname     新路径
 *  @return     bool
 *              成功          true
 *              失败          false
*/
bool set_cwd(char const* pathname);

/*
 *  @property   文件夹处理函数
 *  @func       创建新的文件夹
 *  @param_in   pathname     文件夹名字
 *  @return     bool
 *              成功          true
 *              失败          false
*/

/********************************************************************
 *~~~~~~~~~~~~~~~~~~~~~文件系统文件相关操作~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *******************************************************************/
bool mkdir(char const* pathname);
/*
 *  @property   文件夹处理函数
 *  @func       删除文件夹
 *  @param_in   pathname     文件夹名字
 *  @return     bool
 *              成功          true
 *              失败          false
*/
bool rmdir(char const* pathname);
/*
 *  @property   文件处理函数
 *  @func       断开相关链接的文件
 *  @param_in   pathname     文件名字
 *  @return     bool
 *              成功          true
 *              失败          false
*/
bool unlink(char const* pathname);

/*
 *  @property   文件处理函数
 *  @func       重命名文件
 *  @param_in   pathname     文件名字
 *  @return     bool
 *              成功          true
 *              失败          false
*/
bool rename(char const* from, char const* to);
/*
 *  @property   文件处理函数
 *  @func       复制文件
 *  @param_in   src     源文件名
 *              dst     目标文件名
 *              type 1  文本复制
 *                   else  二进制
 * 默认二进制读写。
*/
void copy_file(char const* src, char const* dst,int type = 0);

/********************************************************************
 *~~~~~~~~~~~~~~~~~~~~~文件系统IO相关操作~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *******************************************************************/

/*
 *  @property   文件IO处理函数
 *  @func       读取文件内容到字符串中
 *  @param_in   filename     文件名
 *  @param_in   data         字符串引用
*/
void read_file_to_string(std::string const& filename,std::string& data);

/*
 *  @property   文件IO处理函数
 *  @func       读取字符串内容到文件中 原文家内容将被覆盖，写成c语言，可以提高效率
 *  @param_in   data         字符串引用
 *  @param_in   filename     文件名
*/
void write_string_to_file(std::string const& data,std::string const& filename);


/********************************************************************
 *~~~~~~~~~~~~~~~~~~~~文件系统字符串相关操作~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *******************************************************************/

/*
 *  @property   文件获取字符串处理函数
 *  @func       获取当前进程执行所在的路径的字符串
 *  @return     std::string     当前进程所在路径字符串
*/
std::string get_cwd_string(void);

/*
 *  @property   文件获取字符串处理函数
 *  @func       获取当前可执行程序执行的路径的字符串
 *  @return     std::string     当前可执行程序路径字符串，包括可执行程序名
*/
std::string get_binary_path(void);

/*
 *  @property   文件路径字符串处理函数
 *  @func       判断path是否为绝对路径
 *  @param_in   待判断路径
 *  @return     bool
 *              是       1
 *              否       0
*/
bool is_absolute_path(std::string const& path);

/*
 *  @property   文件获取字符串处理函数
 *  @func       规范化路径        代替路径中 // => /;     \\ => \
 *  @param_in   path            待处理路径
 *  @return     std::string     处理后的路径
*/
std::string sanitize_path(std::string const& path);

/*
 *  @property   文件获取字符串处理函数
 *  @func       连接path1与path2 path2为path1下的自路径
 *  @param_in   path1           父路径
 *  @param_in   path2           子路径
 *  @return     std::string     处理后的路径 path1+'/'+path2
*/
std::string join_path(std::string const&path1,std::string const& path2);

/*
 *  @property   文件获取字符串处理函数
 *  @func       获取当前进程所在路径（父路径）下的文件或文件夹path的绝对路径
 *  @param_in   path            父路径下子路径
 *  @return     std::string     path的绝对路径
*/
std::string get_absolute_path(std::string const& path);

/*
 *  @property   文件获取字符串处理函数
 *  @func       获取给定路径的文件夹路径部分
 *  @param_in   path            待处理路径
 *  @return     std::string     path的文件夹路径
*/
//TODO:需要修改代码 保证正确性 path最后为/或者文件名才正确，如果最后是文件夹则需要判断
std::string get_directory_name(std::string const& path);

/*
 *  @property   文件获取字符串处理函数
 *  @func       获取给定路径的文件名路径部分
 *  @param_in   path            待处理路径
 *  @return     std::string     path的文件名部分
*/
//TODO:为了便于理解 重写，此处包含了文件夹名
std::string basename(std::string const& path);

/*
 *  @property   文件获取字符串处理函数
 *  @func       给定无后缀文件名加上.extension后缀
 *  @param_in   file            文件名
 *  @param_in   extension       后缀名
 *  @return     std::string     待后缀的文件名
*/
std::string replace_extension(std::string const& file, std::string const& extension);


/********************************************************************
 *~~~~~~~~~~~~~~~~~~~~文件系统文件结构体声明~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *******************************************************************/

/*
 *  @property   文件结构体
 *  @func       文件结构体包含 路径 文件名，按照原定义，包含文件 文件夹
 *  @param_in   path            路径
 *  @param_in   name            文件名
 *  @param_in   is_directory    是否文件夹
*/
struct File
{
    std::string path;
    std::string name;
    bool is_directory;

    File(void);
    File(std::string const& path,std::string const& name, bool is_directory = false);

    /*
     *  @property   获取文件结构体绝对路径
     *  @func       获取File结构体绝对路径
     *  @return     std::string         文件名绝对路径
    */
    std::string get_absolute_name(void) const;

    /*
     *  @property   重载
     *  @func       <文件结构体大小比较
     *  @return     bool
     *              left hand side < right hand side    true
     *              left hand side > right hand side    false
    */
    bool operator<(File const& rhs) const;
};

/*******************************************************************
*~~~~~~~~~~~~~~~~~~~~~~~文件系统目录类声明~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*******************************************************************/
class Directory:public std::vector<File>
{
public:
    Directory(void);
    Directory(std::string const& path);
    /*
     *  @property   获取文件结构体绝对路径
     *  @func       扫描path路径下所有的文件 并存在Directory中
     *  path        输入路径
     *  @return     void
    */
    void scan(std::string const& path);
};

/*******************************************************************
*~~~~~~~~~~~~~~~~~~~~~~~文件系统文件锁机制类~~~~~~~~~~~~~~~~~~~~~~~~~~~
*******************************************************************/
class FileLock
{

};


inline
file_system::File::File()
        :is_directory(false)
{
}

inline
file_system::File::File(std::string const &path, std::string const &name, bool is_directory)
        :path(path),name(name),is_directory(is_directory)
{
}

inline
file_system::Directory::Directory(void)
{
}

inline
file_system::Directory::Directory(std::string const &path)
{
    this->scan(path);
}
FILE_SYSTEM_NAMESPACE_END
UTIL_NAMESPACE_END
#endif //MATH_FILE_SYSTEM_H

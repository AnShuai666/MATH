/*
 * 日期:	2018-12-1
 * 时间:	10:12
 * 姓名:	安帅
 * @func    文件系统
*/

#ifndef MATH_FILE_SYSTEM_H
#define MATH_FILE_SYSTEM_H
#include <string>
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


/********************************************************************
 *~~~~~~~~~~~~~~~~~~~~文件系统字符串相关操作~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *******************************************************************/

void read_file_to_string(std::string const& filename,std::string* data);

void write_string_to_file(std::string const& data,std::string const& filename);

void write_string_to_file(char const* data,std::size_t length,std::string const& filename);





FILE_SYSTEM_NAMESPACE_END
UTIL_NAMESPACE_END
#endif //MATH_FILE_SYSTEM_H

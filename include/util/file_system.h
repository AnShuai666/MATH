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
 *  @func       获取用户目录/home/user
 *  @return     char const*     用户目录
*/
char const* get_home_dir(void);

char* get_cwd(char* buf,std::size_t size);

bool set_cwd(char const* pathname);

bool mkdir(char const* pathname);

bool rmdir(char const* pathname);

bool unlink(char const* pathname);

bool rename(char const* from, char const* to);

void copy_file(char const* src, char const* dst);






FILE_SYSTEM_NAMESPACE_END
UTIL_NAMESPACE_END
#endif //MATH_FILE_SYSTEM_H

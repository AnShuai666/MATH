/*
 * 日期:	2018-12-1
 * 时间:	10:12
 * 姓名:	安帅
 * @func    矩阵类 矩阵常规运算
*/

#ifndef MATH_FILE_SYSTEM_H
#define MATH_FILE_SYSTEM_H
#include <string>
#include "define.h"

UTIL_NAMESPACE_BEGIN
FILE_SYSTEM_NAMESPACE_BEGIN
bool dir_exists(char const* pathname);

bool file_exists(char const* pathname);

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

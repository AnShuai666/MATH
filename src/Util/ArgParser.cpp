/*
 * 日期:	2019-4-24
 * 时间:	21:01
 * 姓名:	安帅
 * @func    参数解析
*/

#include "Util/ArgParser.h"
#include <limits>

UTIL_NAMESPACE_BEGIN
/********************************************************************
 *~~~~~~~~~~~~~~~~~~~~~~~~参数解析类实现~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *******************************************************************/
Arguments::Arguments(void)
    :nonoption_min(0)
    ,nonoption_max(std::numeric_limits<std::size_t>::max())
    ,auto_exit(false)
    ,help_text_indent(16)
    ,description_text_width(75)
    ,current_result(std::numeric_limits<std::size_t>::max())
{
}

void
Arguments::set_usage(const char *argv0, std::string const &usage)
{
    std::stringstream ss;
    ss << "Usage: " << argv0 <<" " << usage;
    this->usage_str = ss.str();
}

UTIL_NAMESPACE_END
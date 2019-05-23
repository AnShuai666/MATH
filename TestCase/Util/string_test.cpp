/*
 * 日期:	2019-5-23
 * 时间:	10:06
 * 姓名:	安帅
 * @func    字符串文件函数测试
*/

#include <iostream>
//这两个宏必须要 我也不知道为什么
#define BOOST_AUTO_TEST_MAIN
#define BOOST_TEST_DYN_LINK

#include <boost/test/unit_test.hpp>
#include "MATH/Util/string.h"

using namespace math;

BOOST_AUTO_TEST_SUITE(minimal_test)

BOOST_AUTO_TEST_CASE(convert_test)
{
    BOOST_CHECK(util::convert<int>("12345", false) == 12345);

}

BOOST_AUTO_TEST_SUITE_END()


/*
 * @desc    测试image_io
 * @author  安帅
 * @date    2019-5-21
 * @e-mail   1028792866@qq.com
*/
//这两个宏必须要 我也不知道为什么
#define BOOST_AUTO_TEST_MAIN
#define BOOST_TEST_DYN_LINK

#include <boost/test/unit_test.hpp>
#include <iostream>
#include "MATH/Util/string.h"
using namespace math;

BOOST_AUTO_TEST_SUITE(minimal_test)

    std::string str = "12345\n\r";

    BOOST_AUTO_TEST_CASE(convert_test)
    {
        BOOST_CHECK(util::convert<int>("12345", false) == 12345);
        BOOST_CHECK(util::convert<int>("23456",true) == 23456);
        BOOST_CHECK(util::convert<int>("34567") == 34567);
    }

    BOOST_AUTO_TEST_CASE(word_wrap_test)
    {
        BOOST_CHECK(util::word_wrap("12345678901234567890",5) == "12345\n67890\n12345\n67890\n");
    }

    BOOST_AUTO_TEST_CASE(clip_newlines_test)
    {
        str = "12345\n\r";
        util::clip_newlines(str);
        BOOST_CHECK( str == "12345");
    }

    BOOST_AUTO_TEST_CASE(clip_whitespaces_test)
    {
        std::string str2 = "\t 12345";
        util::clip_whitespaces(str2);
        std::cout << str2 << std::endl;
        BOOST_CHECK(str2 == "12345");
    }

    BOOST_AUTO_TEST_CASE(uppercase_alpha_numeric_only_test)
    {
        std::string str1 = "Asahi Optical Co.,Ltd.  PENTAX Optio330RS";
        BOOST_CHECK(util::uppercase_alpha_numeric_only(str1) == "ASAHI OPTICAL CO LTD PENTAX OPTIO330RS");
    }


BOOST_AUTO_TEST_SUITE_END()

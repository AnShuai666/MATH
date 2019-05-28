/*
 * @desc    测试image_io
 * @author  安帅
 * @date    2019-5-27
 * @e-mail   1028792866@qq.com
*/
//这两个宏必须要 我也不知道为什么
#define BOOST_AUTO_TEST_MAIN
#define BOOST_TEST_DYN_LINK

#include <boost/test/unit_test.hpp>
#include <iostream>
#include "MATH/Matrix/vector.hpp"
using namespace math;

BOOST_AUTO_TEST_SUITE(minimal_test)

    //第七个构造函数
    BOOST_AUTO_TEST_CASE(Vector_7)
    {
        matrix::Vector2f vector2f(1.1,2.1);
        matrix::Vector3f vector3f(vector2f,1.1);
        BOOST_CHECK( vector3f == matrix::Vector3f(1.1,2.1,1.1));
    }

BOOST_AUTO_TEST_SUITE_END()

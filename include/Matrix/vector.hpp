/*
 * 日期:	2018-12-7
 * 时间:	10:12
 * 姓名:	安帅
 * @func    向量类 向量常规运算
*/

#ifndef __VECTOR_H__
#define __VECTOR_H__

#include <iostream>
#include "define.h"
using namespace std;
VECTOR_NAMESPACE_BEGIN

/********************************************************************
 *~~~~~~~~~~~~~~~~~~~~~常用向量类型别名声明~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *******************************************************************/
template <typename T,int m> class Vector;
typedef Vector<char,1> Vector1c;
typedef Vector<char,2> Vector2c;
typedef Vector<char,3> Vector3c;
typedef Vector<char,4> Vector4c;
typedef Vector<char,5> Vector5c;
typedef Vector<char,6> Vector6c;
typedef Vector<short,64> Vector64s;
typedef Vector<unsigned short,128> Vector128s;
typedef Vector<int,1> Vector1i;
typedef Vector<int,2> Vector2i;
typedef Vector<int,3> Vector3i;
typedef Vector<int,4> Vector4i;
typedef Vector<int,5> Vector5i;
typedef Vector<int,6> Vector6i;
typedef Vector<unsigned int,1> Vector1ui;
typedef Vector<unsigned int,2> Vector2ui;
typedef Vector<unsigned int,3> Vector3ui;
typedef Vector<unsigned int,4> Vector4ui;
typedef Vector<unsigned int,5> Vector5ui;
typedef Vector<unsigned int,6> Vector6ui;
typedef Vector<std::size_t ,1> Vector1st;
typedef Vector<std::size_t ,2> Vector2st;
typedef Vector<std::size_t ,3> Vector3st;
typedef Vector<std::size_t ,4> Vector4st;
typedef Vector<std::size_t ,5> Vector5st;
typedef Vector<std::size_t ,6> Vector6st;
typedef Vector<float,1> Vector1f;
typedef Vector<float,2> Vector2f;
typedef Vector<float,3> Vector3f;
typedef Vector<float,4> Vector4f;
typedef Vector<float,5> Vector5f;
typedef Vector<float,6> Vector6f;
typedef Vector<float,64> Vector64f;
typedef Vector<float,128> Vector128f;
typedef Vector<double,1> Vector1d;
typedef Vector<double,2> Vector2d;
typedef Vector<double,3> Vector3d;
typedef Vector<double,4> Vector4d;
typedef Vector<double,5> Vector5d;
typedef Vector<double,6> Vector6d;


/********************************************************************
 *~~~~~~~~~~~~~~~~~~~~~~~~~Vector类的声明~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *******************************************************************/
    template <typename T,int m>
    class Vector
    {
        //声明向量维度，static保证必须初始化时给定行列值
        static int constexpr dim = m;
/********************************************************************
 *~~~~~~~~~~~~~~~~~~~~~构造函数与析构函数~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *******************************************************************/


        /*
         *  @property   默认构造函数
         *  @func       对向量的dim进行初始化
        */
        Vector();

        /*
         *  @property   普通构造函数
         *  @func       用存在的向量（m维的数组）进行初始化
         *  @exlpicit   防止隐式转换修改成员参数值
         *  @param_in   arr
        */
        explicit Vector(T const *arr);

        /*
         *  @property   普通构造函数
         *  @func       用value对向量（m维的数组）进行初始化
         *  @exlpicit   防止隐式转换修改成员参数值
         *  @param_in   value
        */
        explicit Vector(T const &value);

        /*
        *  @property   普通构造函数
        *  @func       用value1与value2对向量（m维的数组）前两位进行初始化
        *  @param_in   value1
        *  @param_in   value2
        */
        Vector(T const &value1,T const &value2);

        /*
        *  @property   普通构造函数
        *  @func       用value1,value2与value3对向量（m维的数组）前三位进行初始化
        *  @param_in   value1
        *  @param_in   value2
        *  @param_in   value3
        */
        Vector(T const &value1,T const &value2,T const &value3);

        /*
        *  @property   普通构造函数
        *  @func       用value1,value2,value3与value4对向量（m维的数组）前四位进行初始化
        *  @param_in   value1
        *  @param_in   value2
        *  @param_in   value3
        *  @param_in   value4
        */
        Vector(T const &value1,T const &value2,T const &value3,T const &value4);

        /*
        *  @property   普通构造函数
        *  @func       用m-1维的向量与value1对向量（m维的数组）进行初始化
        *  @param_in   vector1
        *  @param_in   value
        */
        Vector(Vector<T,m-1> const &vector1, T const &value);

        /*
         *  @property   拷贝构造函数
         *  @func       用同一类型的vector1对向量（m维的数组）进行初始化
         *  @param_in   vector1
        */
        Vector(Vector<T,m> const& vector1);

        /*
         *  @property   拷贝构造函数
         *  @func       用任意类型的vector1对向量（m维的数组）进行初始化
         *  @param_in   vector1
        */
        template <typename T1>
        Vector(Vector<T1,m> const &vector1);

        /*
         *  @property   析构函数
         *  @func       释放V内存
        */
        ~Vector();

    protected:
        T V[m];

    };

/********************************************************************
 *~~~~~~~~~~~~~~~~~~~~~Vector成员函数实现~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *******************************************************************/
    template <typename T,int m>
    inline
    Vector<T,m>::Vector()
    {

    }

    template <typename T,int m>
    inline
    Vector<T,m>::Vector(T const *arr)
    {
        std::copy(arr,arr + m,V);
    }

    template <typename T,int m>
    inline
    Vector<T,m>::Vector(T const &value)
    {
        std::fill(V,V + m, value);
    }

    template <typename T,int m>
    inline
    Vector<T,m>::Vector(T const &value1,T const &value2)
    {
        V[0] = value1;
        V[1] = value2;
    }

    template <typename T,int m>
    inline
    Vector<T,m>::Vector(T const &value1,T const &value2,T const &value3)
    {
        V[0] = value1;
        V[1] = value2;
        V[2] = value3;
    }

    template <typename T,int m>
    inline
    Vector<T,m>::Vector(T const &value1,T const &value2,T const &value3,T const &value4)
    {
        V[0] = value1;
        V[1] = value2;
        V[2] = value3;
        V[3] = value4;
    }

    template <typename T,int m>
    inline
    Vector<T,m>::Vector(Vector<T,m-1> const &vector1, T const &value)
    {
        std::copy(vector1.V,vector1.V + m-1,V);
        V[m] = value;
    }

    template <typename T,int m>
    inline
    Vector<T,m>::Vector(Vector<T,m> const& vector1)
    {
        std::copy(vector1.V,vector1.V + m,V);
    }


    template <typename T,int m>
    template <typename T1>
    inline
    Vector<T,m>::Vector(Vector<T1,m> const &vector1)
    {
        std::copy(vector1.V,vector1.V + m, V);
    }

    template <typename T,int m>
    inline
    Vector<T,m>::~Vector()
    {
        delete []V;
    }


VECTOR_NAMESPACE_END
#endif //__VECTOR_H__
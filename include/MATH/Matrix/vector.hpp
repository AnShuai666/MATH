/*
 * 日期:	2018-12-7
 * 时间:	10:12
 * 姓名:	安帅
 * @func    向量类 向量常规运算
*/

#ifndef __MATRIX_VECTOR_H__
#define __MATRIX_VECTOR_H__

#include <iostream>
#include <iomanip>
#include "define.h"
#include <algorithm>
#include <iterator>
#include "../math_define.h"
using namespace std;
MATH_NAMESPACE_BEGIN
MATRIX_NAMESPACE_BEGIN

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

typedef Vector<unsigned char,1> Vector1uc;
typedef Vector<unsigned char,2> Vector2uc;
typedef Vector<unsigned char,3> Vector3uc;
typedef Vector<unsigned char,4> Vector4uc;
typedef Vector<unsigned char,5> Vector5uc;
typedef Vector<unsigned char,6> Vector6uc;

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
public:
    //声明向量维度，static保证必须初始化时给定行列值
    static int constexpr dim = m;
/********************************************************************
*~~~~~~~~~~~~~~~~~~~~~构造函数与析构函数~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*******************************************************************/

    public:
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
    //~Vector();//没有new 不需要析构

/********************************************************************
*~~~~~~~~~~~~~~~~~~~~~~~~Vector迭代器~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
********************************************************************/
public:
    /*
    *  @property   迭代器
    *  @func       代表向量第一个元素的指针
    *  @const1     防止修改返回指针
    *  @const2     防止修改类变量
    *  @return     T*
    */
    T* begin();

    /*
    *  @property   迭代器
    *  @func       代表向量第一个元素的指针
    *  @const1     防止修改返回指针
    *  @const2     防止修改类变量
    *  @return     T const*
    */
    T const* begin() const;

    /*
    *  @property   迭代器
    *  @func       代表向量最后一个元素的指针的下一个
    *  @const1     防止修改返回指针
    *  @const2     防止修改类变量
    *  @return     T*
    */
    T* end();

    /*
    *  @property   迭代器
    *  @func       代表向量最后一个元素的指针的下一个
    *  @const1     防止修改返回指针
    *  @const2     防止修改类变量
    *  @return     T const*
    */
    T const* end() const;

/********************************************************************
*~~~~~~~~~~~~~~~~~~~~~~Vector运算符重载~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*******************************************************************/
public:
    /*
    *  @property   重载运算符*
    *  @func       对向量进行解引用,返回地址中保存的值V
    *  @return     T*
    */
    T* operator* ();

    /*
    *  @property   重载运算符*
    *  @func       对向量进行解引用,返回地址中保存的值V
    *  @return     T const*
    */
    T const* operator* () const;

    /*
    *  @property   重载运算符[]
    *  @func       访问向量V元素 V[index]
    *  @param_in   index
    *  @return     T&
    */
    T& operator[] (int index);

    /*
    *  @property   重载运算符[]
    *  @func       访问向量V元素 V[index]
    *  @param_in   index
    *  @return     T const&
    */
    T const& operator[] (int index) const;

    /*
    *  @property   重载运算符()
    *  @func       访问向量V元素 V(index)
    *  @param_in   index
    *  @return     T&
    */
    T& operator() (int index);

    /*
    *  @property   重载运算符()
    *  @func       访问向量V元素 V(index)
    *  @param_in   index
    *  @return     T const&
    */
    T const& operator() (int index) const;

    /*
    *  @property   重载运算符+=
    *  @func       将向量与vector1对应元素相加
    *  @param_in   vector1
    *  @return     Vector<T,m>&
    */
    Vector<T,m>& operator+= (Vector<T,m> const& vector1);

    /*
    *  @property   重载运算符+
    *  @func       将向量与vector1对应元素相加
    *  @param_in   vector1
    *  @return     Vector<T,m>&
    */
    Vector<T,m>& operator+ (Vector<T,m> const& vector1) const;

    /*
    *  @property   重载运算符+=
    *  @func       将向量每个元素对加上value
    *  @param_in   value
    *  @return     Vector<T,m>&
    */
    Vector<T,m>& operator+= (T const& value);

    /*
    *  @property   重载运算符+
    *  @func       将向量每个元素对加上value
    *  @param_in   value
    *  @return     Vector<T,m>&
    */
    Vector<T,m> operator+ (T const& value) const;

    /*
    *  @property   重载运算符-=
    *  @func       将向量与vector1对应元素相加
    *  @param_in   vector1
    *  @return     Vector<T,m>&
    */
    Vector<T,m>& operator-= (Vector<T,m> const& vector1);

    /*
    *  @property   重载运算符-
    *  @func       将向量与vector1对应元素相加
    *  @param_in   vector1
    *  @return     Vector<T,m>&
    */
    Vector<T,m> operator- (Vector<T,m> const& vector1) const;

    /*
    *  @property   重载运算符-=
    *  @func       将向量每个元素对加上value
    *  @param_in   value
    *  @return     Vector<T,m>&
    */
    Vector<T,m>& operator-= (T const& value);

    /*
    *  @property   重载运算符-
    *  @func       将向量每个元素对加上value
    *  @param_in   value
    *  @return     Vector<T,m>&
    */
    Vector<T,m>& operator- (T const& value) const;

    /*
    *  @property   重载运算符*=
    *  @func       将向量每个元素对乘上value 数乘
    *  @param_in   value
    *  @return     Vector<T,m>&
    */
    Vector<T,m>& operator*= (T const value);

    /*
    *  @property   重载运算符*
    *  @func       将向量每个元素对乘上value 数乘
    *  @param_in   value
    *  @return     Vector<T,m>&
    */
    Vector<T,m> operator* (T const value) const;

    /*
    *  @property   重载运算符/
    *  @func       将向量每个元素对乘上value 数乘
    *  @param_in   value
    *  @return     Vector<T,m>&
    */
    Vector<T,m>& operator/= (T const value);

    /*
    *  @property   重载运算符/
    *  @func       将向量每个元素对乘上value 数乘
    *  @param_in   value
    *  @return     Vector<T,m>&
    */
    Vector<T,m> operator/ (T const value) const;

    /*
    *  @property   重载运算符==
    *  @func       比较两向量是否相等
    *  @param_in   vector1
    *  @return     bool
    */
    bool operator== (Vector<T,m> const& vector1) const;

/*
    *  @property   重载运算符!=
    *  @func       比较两向量是否不相等
    *  @param_in   vector1
    *  @return     bool
    */
    bool operator!= (Vector<T,m> const& vector1) const;

    /*
    *  @property   重载运算符=
    *  @func       赋值运算符 同类型赋值
    *  @param_in   vector1
    *  @return     bool
    */
    Vector<T,m>& operator= (Vector<T,m> const& vector1);

    /*
    *  @property   重载运算符=
    *  @func       赋值运算符 任意类型赋值
    *  @param_in   vector1
    *  @return     bool
    */
    template <typename T1>
    Vector<T,m>& operator= (Vector<T1,m> const& vector1);

    /*
    *  @property   重载运算符<<
    *  @func       输出运算符
    *  @param_in   vector1
    *  @return     bool
    */
    template <typename T1,int m1>
    friend ostream & operator<< (ostream& out,const Vector<T1,m1>&);



/********************************************************************
*~~~~~~~~~~~~~~~~~~~~~~Vector管理函数~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
********************************************************************/
public:
    /*
    *  @property   复制
    *  @func       将指针首地址到m个元素拷贝到向量中
    *  @param_in   arr
    *  @param_in   m
    *  @return     Vector<T,m>&
    */
    Vector<T,m>& copy(T const* arr, int num = m );

    /*
    *  @property   求最小值
    *  @func       求向量的最小值
    *  @const      防止修改类变量
    *  @return     T
    */
    T minimum() const;

    /*
    *  @property   求最大值
    *  @func       求向量的最大值
    *  @const      防止修改类变量
    *  @return     T
    */
    T maximum() const;

    /*
    *  @property   求和
    *  @func       求向量所有元素的和
    *  @const      防止修改类变量
    *  @return     T
    */
    T sum() const;

    /*
    *  @property   求绝对值和
    *  @func       求向量所有元素绝对值的和
    *  @const      防止修改类变量
    *  @return     T
    */
    T abs_sum() const;

    /*
    *  @property   求积
    *  @func       求向量所有元素的积
    *  @const      防止修改类变量
    *  @return     T
    */
    T product() const;


/********************************************************************
*~~~~~~~~~~~~~~~~~~~~~~Vector一元运算~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
********************************************************************/
public:
    /*
    *  @property   求模长
    *  @func       求向量的模长或者长度
    *  @const      防止修改类变量
    *  @return     T
    */
    T norm() const;

    /*
    *  @property   求模长平方
    *  @func       求向量的模长或者长度的平方
    *  @const      防止修改类变量
    *  @return     T
    */
    T norm_square() const;

    /*
    *  @property   向量归一化
    *  @func       将向量归一化,即模长为1的向量,原向量被改变
    *  @return     Vector<T,m>&
    */
    Vector<T,m>& normalize();

    /*
    *  @property   向量归一化
    *  @func       求向量的归一化,即模长为1的向量,原向量不改变
    *  @return     Vector<T,m>&
    */
    Vector<T,m> normalized() const;

    /*
    *  @property   求向量绝对值
    *  @func       将向量每个元素求绝对值,原向量被改变
    *  @return     Vector<T,m>&
    */
    Vector<T,m>& abs_value();

    /*
    *  @property   求向量绝对值
    *  @func       将向量每个元素求绝对值,原向量不改变
    *  @return     Vector<T,m>
    */
    Vector<T,m> abs_valued() const;

    /*
    *  @property   求向量相反值
    *  @func       将向量每个元素求相反数,原向量被改变
    *  @return     Vector<T,m>&
    */
    Vector<T,m>& negate();

    /*
    *  @property   求向量相反值
    *  @func       将向量每个元素求相反数,原向量不改变
    *  @return     Vector<T,m>
    */
    Vector<T,m> negated() const;

    /*
    *  @property   升序排序
    *  @func       将向量进行升序排序,原向量被改变
    *  @return     Vector<T,m>&
    */
    Vector<T,m>& sort_ascending();

    /*
    *  @property   升序排序
    *  @func       将向量进行升序排序,原向量不改变
    *  @return     Vector<T,m>
    */
    Vector<T,m> sorted_ascending() const;

    /*
    *  @property   降序排序
    *  @func       将向量进行降序排序,原向量被改变
    *  @return     Vector<T,m>&
    */
    Vector<T,m>& sort_desascending();

    /*
    *  @property   降序排序
    *  @func       将向量进行降序排序,原向量不改变
    *  @return     Vector<T,m>
    */
    Vector<T,m> sorted_desascending() const;

/********************************************************************
*~~~~~~~~~~~~~~~~~~~~~~Vector二元运算~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
********************************************************************/
public:
    /*
    *  @property    內积\标量积\点乘
    *  @func       求两个向量内积
    *  @const      防止修改类成员变量
    *  @return     T T(0) T类型存储空间 并初始化为0
    */
    T dot(Vector<T,m> const& vector1) const;

    /*
    *  @property    外积\向量积\叉乘
    *  @func       求两个向量内积 只定义三维外积
    *  @const      防止修改类成员变量
    *  @return     T T(0) T类型存储空间 并初始化为0
    */
    Vector<T,m> cross(Vector<T,m> const& vector1) const;


/********************************************************************
*~~~~~~~~~~~~~~~~~~~~~~Vector相似度计算~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
********************************************************************/


protected:
    T V[m];

};



/********************************************************************
*~~~~~~~~~~~~~~~~~~~~~Vector成员函数实现~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
********************************************************************/
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
    //此处必须用解引用 否则修改不了保护成员变量V
    std::copy(*vector1,*vector1 + m-1,V);
    V[m-1] = value;
}

template <typename T,int m>
inline
Vector<T,m>::Vector(Vector<T,m> const& vector1)
{
    std::copy(*vector1,*vector1 + m,V);
}


template <typename T,int m>
template <typename T1>
inline
Vector<T,m>::Vector(Vector<T1,m> const &vector1)
{
    std::copy(*vector1,*vector1 + m, V);
}

/*
template <typename T,int m>
inline
Vector<T,m>::~Vector()
{
    delete []V;
}
 */

template <typename T, int m>
inline T*
Vector<T,m>::begin()
{
    return V;
}

template <typename T, int m>
inline T const *
Vector<T,m>::begin() const
{
    return V;
}

template <typename T, int m>
inline T*
Vector<T,m>::end()
{
    return V+m;
}

template <typename T, int m>
inline T const *
Vector<T,m>::end() const
{
    return  V+m;
}

template <typename T,int m>
inline T*
Vector<T,m>::operator* ()
{
    return V;
}

template <typename T,int m>
inline     T const*
Vector<T,m>::operator* () const
{
    return V;
}

template <typename T,int m>
inline  T&
Vector<T,m>::operator[] (int index)
{
    return V[index];
}

template <typename T,int m>
inline  T const &
Vector<T,m>::operator[] (int index) const
{
    return V[index];
}

template <typename T,int m>
inline  T&
Vector<T,m>::operator() (int index)
{
    return V[index];
}

template <typename T,int m>
inline  T const&
Vector<T,m>::operator() (int index) const
{
    return V[index];
}

template <typename T,int m>
inline  Vector<T,m>&
Vector<T,m>::operator+= (Vector<T,m> const& vector1)
{
    std::transform(V,V + m, vector1.V,V,std::plus<T>());
    return *this;
}

template <typename T,int m>
inline  Vector<T,m>&
Vector<T,m>::operator+ (Vector<T,m> const& vector1) const
{
    return Vector<T,m>(*this) += vector1;
}

template <typename T,int m>
inline  Vector<T,m>&
Vector<T,m>::operator+= (T const& value)
{
    for (auto& v : V)
        v += value;
    return *this;
}

template <typename T,int m>
inline  Vector<T,m>
Vector<T,m>::operator+ (T const& value) const
{
    return Vector<T,m>(*this) += value;
}

template <typename T,int m>
inline  Vector<T,m>&
Vector<T,m>::operator-= (Vector<T,m> const& vector1)
{
    std::transform(V,V + m, vector1.V,V,std::plus<T>());
    return *this;
}

template <typename T,int m>
inline  Vector<T,m>
Vector<T,m>::operator- (Vector<T,m> const& vector1) const
{
    Vector<T,m>(*this) += vector1;
}

template <typename T,int m>
inline   Vector<T,m>&
Vector<T,m>::operator-= (T const& value)
{
    for (auto& v : V)
        v += value;
    return *this;
}

template <typename T,int m>
inline  Vector<T,m>&
Vector<T,m>::operator- (T const& value) const
{
    for(auto& v : V)
    {
        v +=value;
    }
    return *this;
}

template <typename T, int m>
inline Vector<T,m>&
Vector<T,m>::operator*= (T const value)
{
    for(auto& v : V)
    {
        v *= value;
    }
    return *this;
}

template <typename T, int m>
inline Vector<T,m>
Vector<T,m>::operator* (T const value) const
{
    return Vector<T,m>(*this) *= value;
}

template <typename T, int m>
inline Vector<T,m>&
Vector<T,m>::operator/= (T const value)
{
    for (auto& v : V)
    {
        v /= value;
    }
    return *this;
}

template <typename T,int m>
inline Vector<T,m>
Vector<T,m>::operator/ (T const value) const
{
    return Vector<T,m>(*this) /= value;
}

template <typename T,int m>
inline bool
Vector<T,m>::operator== (Vector<T,m> const& vector1) const
{
    return std::equal(V,V+m,*vector1);
}

template <typename T,int m >
inline bool
Vector<T,m>::operator!= (Vector<T,m> const& vector1) const
{
    return  !std::equal(V,V+m,*vector1);
}

template <typename T,int m>
inline Vector<T,m>&
Vector<T,m>::operator= (Vector<T,m> const& vector1)
{
    std::copy(*vector1,*vector1 + m,V);
    return *this;
}

template <typename T,int m>
template <typename T1>
inline Vector<T,m>&
Vector<T,m>::operator= (Vector<T1,m> const& vector1)
{
    std::copy(*vector1,*vector1 + m,V);
    return *this;
}

template <typename T1,int m1>
ostream& operator<< (ostream& out,const Vector<T1,m1>& vector1)
{
    for (auto& v :vector1)
    {
        out<<setiosflags(ios::right)<<setw(10)<<v<<endl;
    }
    return out;
}


template <typename T, int m>
inline Vector<T,m>&
Vector<T,m>::copy(T const* arr, int num)
{
    std::copy(arr,arr+num,this->V);
    return *this;
}

template <typename T,int m>
inline T
Vector<T,m>::minimum() const
{
    return *std::min_element(V,V+m);
}


template <typename T,int m>
inline T
Vector<T,m>::maximum() const
{
    return *std::max_element(V,V+m);
}



template <typename T,int m>
inline T
Vector<T,m>::sum() const
{
    T sum = 0;
    for (auto& v : V)
        sum += v;
    return sum;
}


template <typename T,int m>
inline T
Vector<T,m>::abs_sum() const
{
    T sum = 0;
    for (auto &v : V)
    {
        if(v<0)
            v = 0 - v;
        sum += v;
    }
    return sum;
}


template <typename T,int m>
inline T
Vector<T,m>::product() const
{
    T product = (T)1;
    for(auto& v:V)
        product *= v;
    return product;
}

template <typename T, int m>
inline T
Vector<T,m>::norm() const
{
    return std::sqrt(norm_square());
}

template <typename T, int m>
inline T
Vector<T,m>::norm_square() const
{
    T sum_square = 0;
    for (auto &v : V)
    {
        sum_square += v * v;
    }
    return sum_square;
}

template <typename T,int m>
inline Vector<T,m>&
Vector<T,m>::normalize()
{
    for (auto& v:V)
    {
        v /= norm();
    }
    return *this;
}
template <typename T,int m>
inline Vector<T,m>
Vector<T,m>::normalized() const
{
    return Vector<T,m>(*this).normalize();
}

template <typename T,int m>
inline Vector<T,m>&
Vector<T,m>::abs_value()
{
    for (auto& v : V)
    {
        if (v < 0)
        {
            v = -v;
        }
    }
    return *this;
}

template <typename T, int m>
inline Vector<T,m>
Vector<T,m>::abs_valued() const
{
    return Vector<T,m>(*this).abs_value();
}

template <typename T,int m>
inline Vector<T,m>&
Vector<T,m>::negate()
{
    for (auto & v : V)
    {
        v = -v;
    }
    return *this;
}

template <typename T,int m>
inline Vector<T,m>
Vector<T,m>::negated() const
{
    return Vector<T,m>(*this).negate();
}

template <typename T, int m>
inline Vector<T,m>&
Vector<T,m>::sort_ascending()
{
    std::sort(V,V+m,std::less<T>());
    return *this;
}

template <typename T, int m>
inline Vector<T,m>
Vector<T,m>::sorted_ascending() const
{
    return Vector<T,m>(*this).sort_ascending();
}

template <typename T, int m>
inline Vector<T,m>&
Vector<T,m>::sort_desascending()
{
    std::sort(V,V+m,std::greater<T>());
    return *this;
}

template <typename T, int m>
inline Vector<T,m>
Vector<T,m>::sorted_desascending() const
{
    return Vector<T,m>(*this).sort_desascending();
}

template <typename T, int m>
inline T
Vector<T,m>::dot(Vector<T,m>const& vector1) const
{
    return std::inner_product(V,V+m,*vector1,T(0));
}

template <typename T, int m>
inline Vector<T,m>
Vector<T,m>::cross(Vector<T,m> const& vector1) const
{
    if (m != 3)
    {
        cout << "只定义了三维向量积!" << endl;
        std::exit(0);
    }
    return Vector<T, 3>((*this)[1] * vector1[2] - (*this)[2] * vector1[1],
                        (*this)[2] * vector1[0] - (*this)[0] * vector1[2],
                        (*this)[0] * vector1[1] - (*this)[1] * vector1[0]);
}

MATRIX_NAMESPACE_END
MATH_NAMESPACE_END

#endif //__MATRIX_VECTOR_H__
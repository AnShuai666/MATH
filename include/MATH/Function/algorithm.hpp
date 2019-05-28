//
// Created by yhl on 18-12-7.
//
#ifndef MATRIX_BASE_ALGORITHM_BASE_H
#define MATRIX_BASE_ALGORITHM_BASE_H

#include "../Matrix/vector.hpp"
#include "define.h"
#include "../math_define.h"

MATH_NAMESPACE_BEGIN
FUNCTION_NAMESPACE_BEGIN
//清除vector中对应delete_list为true的元素
template <typename T>
void vector_clean(std::vector<bool> const& delete_list, std::vector<T>* vector);




//实现
template <typename T>
void
vector_clean(std::vector<bool> const &delete_list, vector<T> *vector)
{
    typename std::vector<T>::iterator vr = vector->begin();
    typename std::vector<T>::iterator vw = vector->begin();
    typename std::vector<bool>::const_iterator dr = delete_list.begin();

    while (vr != vector->end() && dr != delete_list.end())
    {
        //为true的跳过
        if (*dr++)
        {
            vr++;
            continue;
        }
        //vw得到不删除元素的值
        if (vw != vr)
            *vw = *vr;
        vw++;
        vr++;
    }
    //删除vw之后的所有值
    vector->erase(vw,vector->end());
}


FUNCTION_NAMESPACE_END
MATH_NAMESPACE_END
#endif //MATRIX_BASE_ALGORITHM_BASE_H

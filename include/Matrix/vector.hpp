//
// Created by yft on 18-12-4.
//

#ifndef __VECTOR_H__
#define __VECTOR_H__
#include "define.h"
#include "matrix.hpp"
#include <memory>
using namespace matrix;
VECTOR_NAMESPACE_BEGIN
template <typename T>
class Vector:public Matrix<T>
{
private:

public:
    Vector();
    Vector(int m)
    {
        Matrix<T>(m,1);
    }

    typedef shared_ptr<Vector<T>> Ptr;
    typedef Vector<int> VecInt;
    typedef shared_ptr<Vector<float >> PtrVecFloat;



};



VECTOR_NAMESPACE_END
#endif //__VECTOR_H__
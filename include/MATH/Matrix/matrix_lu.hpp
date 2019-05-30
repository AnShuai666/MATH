#ifndef MATH_MATRIX_LU_HPP
#define MATH_MATRIX_LU_HPP

#include <MATH/math_define.h>
#include <cstdlib>
#include "define.h"
MATH_NAMESPACE_BEGIN
    MATRIX_NAMESPACE_BEGIN

//LUP分解
bool LUPDescomposition(float* A, float* L, float* U, int* P,int DN);

//LUP求解方程
void LUPSolve(float* L, float* U, int* P, float* b,float* x,int DN);
void LUPSolve(float* A,float* b,float* x,int DN);
//LU分解
bool LUDescomposition(float* A, float* L, float* U,int n);

//LU求解方程
void LuSolve(float* L, float* U, float* b,float* x,int DN);

//LU求逆(将每列b求出的各列x进行组装)
template<typename _Tp>
bool LuSolveInverse( _Tp* A,int n,float* inv_A)
{
    int DN=n;
    //创建矩阵A的副本，注意不能直接用A计算，因为LUP分解算法已将其改变
    float *_A_mirror   = new float[DN * DN]();
    float *_inv_A_each = new float[DN]();//矩阵逆的各列
    float *_b          =new float[DN]();//b阵为B阵的列矩阵分量
    int   *_P          =new int[DN]();
    float *_L = new float[DN * DN]();
    float *_U = new float[DN * DN]();

    //需要重新将A复制一份
    for(int j = 0; j < DN * DN; j++)
    {
        _A_mirror[j] = (float)A[j];
    }
    bool _des_sucess=LUPDescomposition(_A_mirror, _L, _U, _P, DN);
    //bool _des_sucess = LUDescomposition(_A_mirror,_L,_U,n);
    if(_des_sucess) {
        for (int i = 0; i < DN; i++) {
            //构造单位阵的每一列
            for (int j = 0; j < DN; j++) {
                _b[j] = 0;
            }
            _b[i] = 1;
            LUPSolve (_L, _U, _P, _b,_inv_A_each,DN);
            //LuSolve(_L, _U, _b, _inv_A_each, DN); //L*U*x=b 的解为逆矩阵的列
            for (int j = 0; j < n; j++) {
                inv_A[j * DN + i] = _inv_A_each[j];
            }

        }
    }
    delete[] _A_mirror;
    delete[] _inv_A_each;
    delete[] _b;
    delete[] _L;
    delete[] _U;
    delete[] _P;

    return _des_sucess;
}


    MATRIX_NAMESPACE_END
MATH_NAMESPACE_END
#endif //MATH_MATRIX_LU_HPP

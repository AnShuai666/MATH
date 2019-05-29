#ifndef MATH_MATRIX_LU_HPP
#define MATH_MATRIX_LU_HPP

#include "../math_define.h"
#include <cstdlib>
#include "define.h"
MATH_NAMESPACE_BEGIN
    MATRIX_NAMESPACE_BEGIN

//LUP分解
bool lupDescomposition(float* A, float* L, float* U, int* P,int DN);

//LUP求解方程
void lupSolve(float* L, float* U, int* P, float* b,float* x,int DN);
void lupSolve(float* A,float* b,float* x,int DN);
//LU分解
bool luDescomposition(float* A, float* L, float* U,int n);

//LU求解方程
void luSolve(float* L, float* U, float* b,float* x,int DN);

//LU求逆(将每列b求出的各列x进行组装)
template<typename Tp>
bool luSolveInverse( Tp* A,int n,float* inv_A)
{
    int DN=n;
    //创建矩阵A的副本，注意不能直接用A计算，因为LUP分解算法已将其改变
    float *A_mirror   = new float[DN * DN]();
    float *inv_A_each = new float[DN]();//矩阵逆的各列
    float *b          =new float[DN]();//b阵为B阵的列矩阵分量
    int   *P          =new int[DN]();
    float *L = new float[DN * DN]();
    float *U = new float[DN * DN]();

    //需要重新将A复制一份
    for(int j = 0; j < DN * DN; j++)
    {
        A_mirror[j] = (float)A[j];
    }
    bool _des_sucess=lupDescomposition(A_mirror, L, U , P, DN);
    //bool _des_sucess = luDescomposition(A_mirror,L,U ,n);
    if(_des_sucess) {
        for (int i = 0; i < DN; i++) {
            //构造单位阵的每一列
            for (int j = 0; j < DN; j++) {
                b[j] = 0;
            }
            b[i] = 1;
            lupSolve (L, U , P, b,inv_A_each,DN);
            //luSolve(L, U , b, inv_A_each, DN); //L*U*x=b 的解为逆矩阵的列
            for (int j = 0; j < DN; j++) {
                inv_A[j * DN + i] = inv_A_each[j];
            }

        }
    }
    delete[] A_mirror;
    delete[] inv_A_each;
    delete[] b;
    delete[] L;
    delete[] U ;
    delete[] P;

    return _des_sucess;
}


    MATRIX_NAMESPACE_END
MATH_NAMESPACE_END
#endif //MATH_MATRIX_LU_HPP

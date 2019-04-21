#ifndef MATH_MATRIX_LU_HPP
#define MATH_MATRIX_LU_HPP

#include <math_define.h>
#include "define.h"
MATH_NAMESPACE_BEGIN
    MATRIX_NAMESPACE_BEGIN

//LUP分解
bool LUPDescomposition(float* A, float* L, float* U, int* P,int DN)
{
    int row = 0;
    for (int i = 0;i < DN; i++)
    {
        P[i] = i;
    }
    for (int i = 0; i < DN - 1;i++)
    {
        float p = 0.0;
        for (int j = i; j < DN; j++)
        {
            if (abs( A[j * DN + i]) > p)
            {
                p   = abs(A[j * DN + i]);
                row = j;
            }
        }
        if(0 == p)
        {
            //cout<< "矩阵奇异，无法计算逆" <<endl;
            return false;
        }

        //交换P[i]和P[row]
        int tmp = P[i];
        P[i]        = P[row];
        P[row]      = tmp;

        float tmp2 = 0.0;
        for (int j = 0; j < DN; j++)
        {
            //交换A[i][j]和 A[row][j]
            tmp2 = A[i * DN + j];
            A[i * DN + j]   = A[row * DN + j];
            A[row * DN + j] = tmp2;
        }

        //以下同LU分解
        float u = A[i * DN + i], l = 0.0;
        for (int j = i + 1; j < DN; j++)
        {
            l = A[j * DN + i] / u;
            A[j * DN + i] = l;
            for (int k = i + 1; k < DN; k ++)
            {
                A[j * DN + k] = A[j * DN + k] - A[i * DN + k] * l;
            }
        }
    }

    //构造L和U
    for (int i = 0; i < DN; i++)
    {
        for (int j = 0; j <= i; j++)
        {
            if (i != j)
            {
                L[i * DN + j] = A[i * DN + j];
            }
            else
            {
                L[i * DN + j] = 1;
            }
        }
        for (int k = i; k < DN; k++)
        {
            U[i * DN + k] = A[i * DN + k];
        }
    }
    return true;
}

//LUP求解方程
void LUPSolve(float* L, float* U, int* P, float* b,float* x,int DN)
{
    float *y=new float[DN]();

    //正向替换
    for (int i = 0;i < DN;i++)
    {
        y[i] = b[P[i]];
        for (int j = 0;j < i;j++)
        {
            y[i] = y[i] - L[i * DN + j] * y[j];
        }
    }
    //反向替换
    for (int i = DN-1;i >= 0; i--)
    {
        x[i] = y[i];
        for (int j = DN-1;j > i;j--)
        {
            x[i] = x[i] - U[i * DN + j] * x[j];
        }
        x[i] /= U[i * DN + i];
    }
    delete[] y;
}

//LU分解
bool LUDescomposition(float* A, float* L, float* U,int n)
{

    int i, r, k;
    //进行U的第一行的赋值
    for (i = 0; i<n; i++)
    {
        U[i] = A[i];
    }

    //进行L的第一列的赋值
    for (i = 1; i<n; i++)
    {
        L[i*n] = A[i*n] / U[0];
    }
    double eps=1e-7;
    //计算U的剩下的行数和L的剩下的列数
    for (r = 1; r<n; r++)
    {
        for (i = r; i <n; i++)
        {
            float sum1 = 0;
            for (k = 0; k < r; k++)
            {
                sum1 += L[r*n+k] * U[k*n+i];
                //cout << "" << r << "" << sum1 << endl;
            }
            U[r*n+i] = A[r*n+i] - sum1;
        }
        if(abs(U[r*n+r])<eps)
            return false;



        for(i=r+1;i<n;i++)
        {
            float sum2 = 0;
            for (k = 0; k<r; k++)
            {
                sum2 += L[i*n+k] * U[k*n+r];
            }
            L[i*n+r] = (A[i*n+r] - sum2) / U[r*n+r];
        }

    }
    for (i = 0; i<n; i++) {
        L[i*n+i]=1;
    }
    return true;
}

//LU求解方程
void LuSolve(float* L, float* U, float* b,float* x,int DN)
{
    float *y=new float[DN]();

    //正向替换
    for (int i = 0;i < DN;i++)
    {
        y[i] = b[i];
        for (int j = 0;j < i;j++)
        {
            y[i] = y[i] - L[i * DN + j] * y[j];
        }
    }
    //反向替换
    for (int i = DN-1;i >= 0; i--)
    {
        x[i] = y[i];
        for (int j = DN-1;j > i;j--)
        {
            x[i] = x[i] - U[i * DN + j] * x[j];
        }
        x[i] /= U[i * DN + i];
    }
    delete[] y;
}

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

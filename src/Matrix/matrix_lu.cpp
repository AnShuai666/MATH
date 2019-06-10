//
// Created by yft on 18-12-4.
//
#include <cstring>
#include <iostream>
#include "MATH/Matrix/matrix_lu.hpp"
MATH_NAMESPACE_BEGIN
        MATRIX_NAMESPACE_BEGIN

inline float absf(float x) {float abs_x=x<0?(-x):x; return abs_x;}
//LUP分解
bool lupDescomposition(const float* in_A, float* L, float* U, int* P,int DN)
{
    float *A=new float[DN*DN];
    memcpy(A,in_A,sizeof(float)*DN*DN);
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
            if (absf( A[j * DN + i]) > p)
            {
                p   = absf(A[j * DN + i]);
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
void lupSolve(const float* L, float* U, int* P, float* b,float* x,int DN)
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
void lupSolve(const float* A,float* b,float* x,int DN)
{
    float* L=new float[DN*DN];
    float* U=new float[DN*DN];
    int* P=new int[DN];
    float *a=new float[DN*DN];
    memcpy(a,A,sizeof(float)*DN*DN);
    lupDescomposition(a,L,U,P,DN);
    lupSolve(L,U,P,b,x,DN);

    delete[] a;
    delete[] L;
    delete[] U;
    delete[] P;
}
//LU分解
bool luDescomposition(const float* A, float* L, float* U,int n)
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
    float eps=1e-7;
    //计算U的剩下的行数和L的剩下的列数
    for (r = 1; r<n; r++)
    {
        for (i = r; i <n; i++)
        {
            float sum1 = 0;
            for (k = 0; k < r; k++)
            {
                sum1 += L[r*n+k] * U[k*n+i];
            }
            U[r*n+i] = A[r*n+i] - sum1;
        }
        if(absf(U[r*n+r])<eps)
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
void luSolve(const float* L, float* U, float* b,float* x,int DN)
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

void luSolve(const float* A, float* b,float* x,int DN)
{
    float* L=new float[DN*DN];
    float* U=new float[DN*DN];
    float *a=new float[DN*DN];
    memcpy(a,A,sizeof(float)*DN*DN);
    luDescomposition(a,L,U,DN);
    luSolve(L,U,b,x,DN);

    delete[] a;
    delete[] L;
    delete[] U;
}
MATRIX_NAMESPACE_END
        MATH_NAMESPACE_END
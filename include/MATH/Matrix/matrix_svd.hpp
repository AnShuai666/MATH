/*
 * 日期:	2018-04-09
 * 时间:	10:58
 * 姓名:	安帅
 * @func    矩阵SVD分解
*/

#ifndef MATH_MATRIX_SVD_HPP
#define MATH_MATRIX_SVD_HPP

#include <MATH/math_define.h>
#include "define.h"
#include <time.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
MATH_NAMESPACE_BEGIN
MATRIX_NAMESPACE_BEGIN


template <typename T>
void svd_decomposition(T const* A,int rows,int coll,T* U,T* S,T* V,const double epsilon = 1e-12);


MATRIX_NAMESPACE_END
MATH_NAMESPACE_END


MATH_NAMESPACE_BEGIN
MATRIX_NAMESPACE_BEGIN


static double eps=1e-12;      //允许的最大误差

double get_norm(double *x, int n)   //求sqrt(x[1]*x[1] + x[2]*x[2] +......+ x[n]*x[n])，                                     //求向量x的模长|x|；
{
    double r=0;
    for(int i=0;i<n;i++)
        r+=x[i]*x[i];
    return sqrt(r);
}


double normalize(double *x, int n)   //当求的的向量x的模小于eps最小值时，舍去；
{                        //当x的模大于eps时，保留；并将x[i]/|x|，将向量x归一化为单位向量e；
    double r=get_norm(x,n);
    if(r<eps)
        return 0;
    for(int i=0;i<n;i++)
        x[i]/=r;
    return r;                 //返回向量x的模长，模长不能太小，
}


inline double product(double*a, double *b,int n)  //求的向量a和向量b的内积，即(a[1]*b[1] + a[2]*b[2] +......+ a[n]*b[n])；
{
    double r=0;
    for(int i=0;i<n;i++)
        r+=a[i]*b[i];
    return r;
}


void orth(double *a, double *b, int n)    //正交化；|a|=1 ，向量a为单位向量e，将向量b与单位
{                                         // 向量进行正交，
    double r=product(a,b,n);        //向量b与单位向量e的内积，即为向量b在单位向量e上的投影值
    for(int i=0;i<n;i++)
        b[i]-=r*a[i];                   //b'[i] = b[i] - (e, b)*b[i] ,得到与向量a正交的向                                         //量b' 即（a, b')的内积为0；
}

bool svd(double** A, int M,int N, double** U, double* S, double** Vt)
{
//矩阵为A(M×N) ，A = U S (V^T)； U(M×K)  S(K×K)  V(N×K)
    int K=M<N?M:N;
    double** Ut=new double*[K];//数组按行存取更方便
    for(int i=0;i<K;i++) {
        Ut[i] = new double[M];
        memset(Ut[i],0,sizeof(double)*M);
        memset(Vt[i],0,sizeof(double)*N);
        S[i]=0;
    }

    srand(time(0));            //给一个随机种子数,

    double *left_vector=new double[M];          //动态分配内存,产生left_vector和                                                           //next_left_vector向量用于迭代运算
    double *next_left_vector=new double[M];
    double *right_vector=new double[N];
    double *next_right_vector=new double[N];

    while(1)
    {
        for(int i=0;i<M;i++)
            left_vector[i]= (float)rand() / RAND_MAX;    //随机生成一个向量vector（即α），                                                       //共有M个元素，用来求解左奇异矩阵
        if(normalize(left_vector, M)>eps)               //当向量的模长大于eps时，生成结束；                                                        //生成一个模长合适的迭代向量
            break;
    }
    const int MAX_ITER=100000;      //迭代器迭代次数
    int col=0;
    for(int col=0;col<K;col++)    //按列计算左右奇异矩阵,迭代
    {
        double diff=1;
        double r=-1;

        for(int iter=0; diff>=eps && iter<MAX_ITER; iter++)     //迭代器iter的迭代次数为10000次
        {
            memset(next_left_vector,0,sizeof(double)*M);
            memset(next_right_vector,0,sizeof(double)*N);  //分配内存给左迭代向量和右迭代向量


            for(int j=0;j<N;j++)
                for(int i=0;i<M;i++)
                    next_right_vector[j]+=left_vector[i]*A[i][j];   //向量α(1×M)×A(M×N)矩阵，得到右迭代向量β_next(1×N)

            r=normalize(next_right_vector,N);                 //单位化向量β_next

            if(r<eps) break;                                  //若β_next 模长太小，则退出内层循环
            for(int i=0;i<col;i++)
                orth(&Vt[i][0],next_right_vector,N);              //与右矩阵V正交，正交化得到β'_next
            normalize(next_right_vector,N);                      //单位化β'_next



            for(int i=0;i<M;i++)
                for(int j=0;j<N;j++)
                    next_left_vector[i]+=A[i][j]*next_right_vector[j]; //矩阵A(M×N)×(β'_next)^T(N×1)向量，得到左迭代向量α_next(M×1)

            r=normalize(next_left_vector,M);                       //单位化向量α_next

            if(r<eps) break;                                       //若α_next 模长太小，则退出内层循环
            for(int i=0;i<col;i++)
                orth(&Ut[i][0],next_left_vector,M);                 //与左矩阵U正交，正交化得到α'_next
            normalize(next_left_vector,M);                         //单位化α'_next

            diff=0;

            for(int i=0;i<M;i++)
            {
                double d=next_left_vector[i]-left_vector[i];      //计算前后两个迭代向量的2范数的平方，即两个向量差距的平方
                diff+=d*d;
            }

            memcpy(left_vector,next_left_vector,sizeof(double)*M);      //拷贝迭代向量的值，使得迭代过程往前进行;强行列向量转行向量，方便存取。
            memcpy(right_vector,next_right_vector,sizeof(double)*N);    //拷贝迭代向量的值，使得迭代过程往前进行;
        }

        if(r>=eps)
        {
            S[col]=r;                                                  //若向量的模长大于最小值eps，则取为矩阵A的奇异值

            memcpy((char *)&Ut[col][0],left_vector,sizeof(double)*M);   //按列拷贝左迭代向量到左奇异矩阵U中

            memcpy((char *)&Vt[col][0],right_vector,sizeof(double)*N);  //按列拷贝右迭代向量到右奇异矩阵V中

        }
        else break;
    }

    for(int i=0;i<K;i++)
    {
        for(int j=0;j<M;j++)
        {
            U[j][i]=Ut[i][j];
        }
    }
    for(int i=0;i<K;i++)
        delete[] Ut[i];
    delete[] Ut;
    delete [] next_left_vector;
    delete [] next_right_vector;
    delete [] left_vector;
    delete [] right_vector;

    return true;
}
bool svd(double* A, int M,int N, double* U, double* S, double* Vt)
{
//矩阵为A(M×N) ，A = U S (V^T)； U(M×K)  S(K×K)  V(N×K)


    int K=M<N?M:N;
    double** Ut=new double*[K];
    for(int i=0;i<K;i++) {
        Ut[i] = new double[M];
        memset(Ut[i],0,sizeof(double)*M);
        memset((Vt+i*N),0,sizeof(double)*N);
        S[i]=0;
    }

    srand(time(0));            //给一个随机种子数,

    double *left_vector=new double[M];          //动态分配内存,产生left_vector和                                                           //next_left_vector向量用于迭代运算
    double *next_left_vector=new double[M];
    double *right_vector=new double[N];
    double *next_right_vector=new double[N];

    while(1)
    {
        for(int i=0;i<M;i++)
            left_vector[i]= (float)rand() / RAND_MAX;    //随机生成一个向量vector（即α），                                                       //共有M个元素，用来求解左奇异矩阵
        if(normalize(left_vector, M)>eps)               //当向量的模长大于eps时，生成结束；                                                        //生成一个模长合适的迭代向量
            break;
    }
    const int MAX_ITER=100000;      //迭代器迭代次数
    int col=0;
    for(int col=0;col<K;col++)    //按列计算左右奇异矩阵,迭代
    {
        double diff=1;
        double r=-1;

        for(int iter=0; diff>=eps && iter<MAX_ITER; iter++)     //迭代器iter的迭代次数为10000次
        {
            memset(next_left_vector,0,sizeof(double)*M);
            memset(next_right_vector,0,sizeof(double)*N);  //分配内存给左迭代向量和右迭代向量


            for(int i=0;i<M;i++)
                for(int j=0;j<N;j++)
                    next_right_vector[j]+=left_vector[i]*A[i*N+j];   //向量α(1×M)×A(M×N)矩阵，得到右迭代向量β_next(1×N)

            r=normalize(next_right_vector,N);                 //单位化向量β_next

            if(r<eps) break;                                  //若β_next 模长太小，则退出内层循环
            for(int i=0;i<col;i++)
                orth((Vt+i*N),next_right_vector,N);              //与右矩阵V正交，正交化得到β'_next
            normalize(next_right_vector,N);                      //单位化β'_next



            for(int i=0;i<M;i++)
                for(int j=0;j<N;j++)
                    next_left_vector[i]+=next_right_vector[j]*A[i*N+j]; //矩阵A(M×N)×(β'_next)^T(N×1)向量，得到左迭代向量α_next(1×M)

            r=normalize(next_left_vector,M);                       //单位化向量α_next

            if(r<eps) break;                                       //若α_next 模长太小，则退出内层循环
            for(int i=0;i<col;i++)
                orth(&Ut[i][0],next_left_vector,M);                 //与左矩阵U正交，正交化得到α'_next
            normalize(next_left_vector,M);                         //单位化α'_next

            diff=0;

            for(int i=0;i<M;i++)
            {
                double d=next_left_vector[i]-left_vector[i];      //计算前后两个迭代向量的2范数的平方，即两个向量差距的平方
                diff+=d*d;
            }

            memcpy(left_vector,next_left_vector,sizeof(double)*M);     //拷贝迭代向量的值，使得迭代过程往前进行
            memcpy(right_vector,next_right_vector,sizeof(double)*N);
        }

        if(r>=eps)
        {
            S[col]=r;                                                  //若向量的模长大于最小值eps，则取为矩阵A的奇异值

            memcpy((char *)&Ut[col][0],left_vector,sizeof(double)*M);   //按列拷贝左迭代向量到左奇异矩阵U中

            memcpy((char *)&Vt[col*N],right_vector,sizeof(double)*N);  //按列拷贝右迭代向量到右奇异矩阵V中

        }
        else break;
    }

    for(int i=0;i<K;i++)
    {
        for(int j=0;j<M;j++)
        {
            U[j*K+i]=Ut[i][j];
        }
    }
    for(int i=0;i<K;i++)
        delete[] Ut[i];
    delete[] Ut;
    delete [] next_left_vector;
    delete [] next_right_vector;
    delete [] left_vector;
    delete [] right_vector;

    return true;
}

/*
 *  @property   SVD分解
 *  @func       将矩阵A进行SVD分解
 *  @param_in   A           待分解矩阵A(MxN)
 *  @param_in   rows        矩阵行数
 *  @param_in   cols        矩阵列数
 *  @param_in_out   U           正交矩阵(MxK)   //K=min(M,N)或指定
 *  @param_in_out   S           正对角元上三角矩阵(KxK)
 *  @param_in_out   V           正交矩阵(KxN)
 *  @param_in   episilon
*/
template <typename T>
void
svd_decomposition(T const *A, int rows, int cols, T *U, T *S, T *V, const double epsilon)
{
    eps=(double)epsilon;
    int k=rows<cols?rows:cols;
    double** U0=new double*[rows];
    for(int i=0;i<rows;i++)
        U0[i]=new double[k];
    double** Vt0=new double*[k];
    for(int i=0;i<cols;i++)
        Vt0[i]=new double[cols];
    double* S0=new double[k];
    double** A0=new double*[rows];
    for(int i=0;i<rows;i++)
    {
        A0[i]=new double[cols];
        for(int j=0;j<cols;j++)
        {
            A0[i][j]=A[i*cols+j];
        }
    }
    svd(A0,rows,cols,U0,S0,Vt0);
    for(int i=0;i<rows;i++){
        for(int j=0;j<k;j++)
            U[i*k+j]=(T)U0[i][j];
    }
    for(int i=0;i<k;i++)
        S[i]=(T)S0[i];
    for(int i=0;i<k;i++){
        for(int j=0;j<cols;j++)
            V[i*cols+j]=(T)Vt0[i][j];
    }
    for(int i=0;i<rows;i++)
        delete[] U0[i];
    delete[] U0;
    for(int i=0;i<rows;i++)
        delete[] A0[i];
    delete[] A0;
    for(int i=0;i<k;i++)
        delete[] Vt0[i];
    delete[] Vt0;
    delete[] S0;
}



MATRIX_NAMESPACE_END
MATH_NAMESPACE_END
#endif //MATH_MATRIX_SVD_HPP

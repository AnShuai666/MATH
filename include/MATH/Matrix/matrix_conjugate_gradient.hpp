/*
 * 日期:	2018-04-09
 * 时间:	11:03
 * 姓名:	安帅
 * @func    矩阵共轭梯度法求解运算
*/

#ifndef MATH_MATRIX_CONJUGATE_GRADIENT_HPP
#define MATH_MATRIX_CONJUGATE_GRADIENT_HPP

#include <MATH/math_define.h>
#include "define.h"

MATH_NAMESPACE_BEGIN
MATRIX_NAMESPACE_BEGIN

static int CG_N=0;
double clcResidue(double* residue,const double** A,const double* b,double* x)//r=b-Ax返回r模长平方
{
    double r=0;
    for(int i=0;i<CG_N;i++) {
        residue[i]=b[i];
        for(int j=0;j<CG_N;j++){
            residue[i]-=A[i][j]*x[j];
        }
        r += residue[i] * residue[i];
    }
    return r;
}
double clcResidue2(double* residue,const double** A,const double* d,double alpha)//r(k+1)=r(k)-alpha*A*d返回r模长平方
{
    double r=0;
    for(int i=0;i<CG_N;i++) {
        for(int j=0;j<CG_N;j++){
            residue[i]-=A[i][j]*d[j]*alpha;
        }
        r += residue[i] * residue[i];
    }
    return r;
}
double clcAlpha(double rtr,double* d,const double** A)//alpha=(r*r)/(d*A*d)
{
    double dtAd=0;
    for(int i=0;i<CG_N;i++)
    {
        double Ajd=0;
        for(int j=0;j<CG_N;j++)
        {

           Ajd+=A[i][j]*d[j];
        }
        dtAd+=Ajd*d[i];
    }
    return rtr/dtAd;
}
void clcNextX(double* x,double* d,double alpha)//x(k+1)=x(k)+alpha*d(k)
{
    for(int i=0;i<CG_N;i++)
        x[i]=x[i]+alpha*d[i];
}
void clcNextDirection(double* d,double* r,double beta)//d(k+1)=r(k+1)+beta*d(x)
{
    for(int i=0;i<CG_N;i++)
        d[i]=r[i]+beta*d[i];
}
double conjugateGradientSlover(const double** in_A,const double* in_b,double *in_x,int n)//计算Ax=b,返回计算误差
{
    CG_N=n;
    double eps=1e-4;
    int max_ite=n*5;
    double *x=new double[n];
    for(int i=0;i<n;i++)
        x[i]=1;
    double *residue=new double[n];
    double res_val=clcResidue(residue,in_A,in_b,x);
    double res_val_previous=res_val;
    double alpha=0;
    double *direction=new double[n];
    for(int i=0;i<n;i++)
        direction[i]=residue[i];
    int k=0;
    while (res_val>eps&&k<max_ite){
        alpha=clcAlpha(res_val_previous,direction,in_A);
        clcNextX(x,direction,alpha);
        res_val=clcResidue(residue,in_A,in_b,x);
        double beta=res_val/res_val_previous;
        clcNextDirection(direction,residue,beta);
        res_val_previous=res_val;
        k++;
        //printf("k=%d , residue=%f\n",k,_res_val);
    }
    for(int i=0;i<n;i++)
        in_x[i]=x[i];
    delete[] direction;
    delete[] x;
    delete[] residue;
    return res_val;
}

template <typename T>
double conjugateGradient(T** in_A,T* in_b,double *in_x,int n){
    double** A=new double*[n];
    double* b=new double[n];
    for(int i=0;i<n;i++)
    {
        b[i]=in_b[i];
        A[i]=new double[n];
        for(int j=0;j<n;j++)
            A[i][j]=(double)in_A[i][j];
    }
    double err=conjugateGradientSlover((const double**)A,b,in_x,n);

    for(int i=0;i<n;i++)
        delete[] A[i];
    delete[] A;
    delete[] b;
    return err;
}


template <typename T>
double conjugateGradient(T* in_A,T* in_b,double *in_x,int n){
    double** A=new double*[n];
    double* b=new double[n];
    for(int i=0;i<n;i++)
    {
        b[i]=in_b[i];
        A[i]=new double[n];
        for(int j=0;j<n;j++)
            A[i][j]=(double)in_A[i*n+j];
    }
    double err=conjugateGradientSlover((const double**)A,b,in_x,n);

    for(int i=0;i<n;i++)
        delete[] A[i];
    delete[] A;
    delete[] b;
    return err;
}
MATRIX_NAMESPACE_END
MATH_NAMESPACE_END

#endif //MATH_MATRIX_CONJUGATE_GRADIENT_HPP

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
double ClcResidue(double* residue,const double** A,const double* b,double* x)//r=b-Ax返回r模长平方
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
double ClcResidue2(double* residue,const double** A,const double* d,double alpha)//r(k+1)=r(k)-alpha*A*d返回r模长平方
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
double ClcAlpha(double rtr,double* d,const double** A)//alpha=(r*r)/(d*A*d)
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
void ClcNextX(double* x,double* d,double alpha)//x(k+1)=x(k)+alpha*d(k)
{
    for(int i=0;i<CG_N;i++)
        x[i]=x[i]+alpha*d[i];
}
void ClcNextDirection(double* d,double* r,double beta)//d(k+1)=r(k+1)+beta*d(x)
{
    for(int i=0;i<CG_N;i++)
        d[i]=r[i]+beta*d[i];
}
double ConjugateGradientSlover(const double** A,const double* b,double *x,int n)//计算Ax=b,返回计算误差
{
    CG_N=n;
    double eps=1e-4;
    int max_ite=n*5;
    double *_x=new double[n];
    for(int i=0;i<n;i++)
        _x[i]=1;
    double *_residue=new double[n];
    double _res_val=ClcResidue(_residue,A,b,_x);
    double _res_val_previous=_res_val;
    double _alpha=0;
    double *_direction=new double[n];
    for(int i=0;i<n;i++)
        _direction[i]=_residue[i];
    int k=0;
    while (_res_val>eps&&k<max_ite){
        _alpha=ClcAlpha(_res_val_previous,_direction,A);
        ClcNextX(_x,_direction,_alpha);
        _res_val=ClcResidue(_residue,A,b,_x);
        double _beta=_res_val/_res_val_previous;
        ClcNextDirection(_direction,_residue,_beta);
        _res_val_previous=_res_val;
        k++;
        //printf("k=%d , residue=%f\n",k,_res_val);
    }
    for(int i=0;i<n;i++)
        x[i]=_x[i];
    delete[] _direction;
    delete[] _x;
    delete[] _residue;
    return _res_val;
}

template <typename T>
double ConjugateGradient(T** A,T* b,double *x,int n){
    double** _A=new double*[n];
    double* _b=new double[n];
    for(int i=0;i<n;i++)
    {
        _b[i]=b[i];
        _A[i]=new double[n];
        for(int j=0;j<n;j++)
            _A[i][j]=(double)A[i][j];
    }
    double _err=ConjugateGradientSlover((const double**)_A,_b,x,n);

    for(int i=0;i<n;i++)
        delete[] _A[i];
    delete[] _A;
    delete[] _b;
    return _err;
}


template <typename T>
double ConjugateGradient(T* A,T* b,double *x,int n){
    double** _A=new double*[n];
    double* _b=new double[n];
    for(int i=0;i<n;i++)
    {
        _b[i]=b[i];
        _A[i]=new double[n];
        for(int j=0;j<n;j++)
            _A[i][j]=(double)A[i*n+j];
    }
    double _err=ConjugateGradientSlover((const double**)_A,_b,x,n);

    for(int i=0;i<n;i++)
        delete[] _A[i];
    delete[] _A;
    delete[] _b;
    return _err;
}
MATRIX_NAMESPACE_END
MATH_NAMESPACE_END

#endif //MATH_MATRIX_CONJUGATE_GRADIENT_HPP

#include "MATH/Matrix/matrix_svd.hpp"
#include "MATH/Matrix/matrix.hpp"
#include "MATH/Matrix/matrix_lu.hpp"
#include<iostream>
using namespace std;

const int n =100;
//矩阵的ALU分解
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
#define N 5
#define epsilon  0.005

void conjugate()
{
    void matrixTimesVec(double A[N][N], double b[N], double Ab[N]);
    double scalarProduct(double vec1[], double vec2[]);
    void vecPlus(double vec1[], double vec2[], double vec[]);
    void numPlusVec(double num, double vec0[], double vec[]);
    int i, j;
    static double A[N][N] = { 0 };
    static double b[N] = { 1, 1, 1, 1, 1 };
    static double x0[N] = { 1, 1, 1, 1, 1 };
    double x[N], r[N], p[N], w[N], alpha, rho00, rho0, rho1, beta;
    //生成一个大规模稀疏矩阵A，这里以三对角为例。




    for (i = 1; i < N - 1; i++)
    {
        A[i][i - 1] = 2;
        A[i][i] = 3;
        A[i][i + 1] = 1;
    }
    A[0][0] = 3; A[0][1] = 1;
    A[N - 1][N - 2] = 2; A[N - 1][N - 1] = 3;


    printf("\n要求解的示例方程组为：\n A ||| b ||| x0\n");
    for (i = 0; i < N; i++)
    {
        for (j = 0; j < N; j++)
        {
            printf("%f ", A[i][j]);
        }
        printf("||| %f||| %f\n", b[i], x0[i]);
    }

    //init
    memcpy(x, x0, N*sizeof(double));
    double Ax0[N];
    matrixTimesVec(A, x0, Ax0);
    numPlusVec(-1.0, Ax0, Ax0);
    vecPlus(b, Ax0, r);
    rho0 = scalarProduct(r, r);
    rho00 = rho0;
    memcpy(p, r, N*sizeof(double));
    do
    {
        matrixTimesVec(A, p, w);
        alpha = rho0 / (scalarProduct(p, w));
        double temp[N];
        numPlusVec(alpha, p, temp);
        double x_temp[N];
        vecPlus(x, temp, x_temp);
        memcpy(x, x_temp, N*sizeof(double));

        numPlusVec(-alpha, w, temp);
        double r_temp[N];
        vecPlus(r, temp, r_temp);
        memcpy(r, r_temp, N*sizeof(double));

        rho1 = scalarProduct(r, r);

        beta = rho1 / rho0;
        numPlusVec(beta, p, temp);
        vecPlus(r, temp, p);
        rho0 = rho1;

    } while (rho1 > epsilon);

    printf("\n\n");
    printf("方程组的解为：\n");
    for (i = 0; i < N; i++)
        printf("%f\n", x[i]);
    getchar();
}

void matrixTimesVec(double A[N][N], double b[N], double Ab[N])
{
    int i, j;


    for (i = 0; i < N; i++)
    {
        Ab[i] = 0.0;
        for (j = 0; j < N; j++)
        {
            Ab[i] = Ab[i] + A[i][j] * b[j];
        }
    }
}

double scalarProduct(double vec1[], double vec2[])
{
    double s = 0;
    int i;
    for (i = 0; i < N; i++)
    {
        s = s + vec1[i] * vec2[i];
    }
    return s;
}
void vecPlus(double vec1[], double vec2[], double vec[])
{
    int i;
    for (i = 0; i < N; i++)
    {
        vec[i] = vec1[i] + vec2[i];
    }
}
void numPlusVec(double num, double vec0[], double vec[])
{
    int i;
    for (i = 0; i < N; i++)
        vec[i] = num*vec0[i];

}
void svd()
{
    const int row=8;
    const int col=6;
    const int K=6;
    float *H=new float[row*col];
    float *S=new float[K];
    float *V=new float[K*col];
    float *U=new float[row*K];
    for(int i=0;i<row;i++)
    {
        for(int j=0;j<col;j++) {
            H[i*col+j] = (rand() % 100) / 10.f;
        }
    }
    svdDecomposition2(H,U,S,V,row,col,K);
//    Mat mats(K,K,CV_32FC1);
//    for(int i=0;i<K;i++)
//        mats.at<float>(i,i)=S[i];
//    Mat matu(row,K,CV_32FC1,U);
//    Mat matv(K,col,CV_32FC1,V);
//    //transpose(matv,matv);
//    Mat mata(row,col,CV_32FC1,H);
//    float err=sum(abs(mata-matu*mats*matv))[0];
//    cout<<err<<endl;
}
int main() {
    conjugate();
    float *H=new float[n*n];
    float *b=new float[n];
    float *x=new float[n];
    float *x2=new float[n];
    for(int i=0;i<n*n;i++)
        H[i]=(rand()%100)/10.f;
    for(int i=0;i<n;i++)
        b[i]=(rand()%100)/10.f;
    Matrix<float ,n,n> matrix(H);
    cout<<matrix.determiniant()<<endl;
    if(matrix.determiniant()==0)
        return 0;
    //cout<<matrix.inverse()<<endl;
    double s=clock();
    for(int i=0;i<10000;i++)
        matrix.inverse();
    cout<<(clock()-s)/CLOCKS_PER_SEC*1000.f<<"ms"<<endl;
    s=clock();
    for(int i=0;i<10000;i++)
        luSolve(H,b,x,n);
    cout<<(clock()-s)/CLOCKS_PER_SEC*1000.f<<"ms"<<endl;
    s=clock();
    for(int i=0;i<10000;i++)
        lupSolve(H,b,x2,n);
    cout<<(clock()-s)/CLOCKS_PER_SEC*1000.f<<"ms"<<endl;
    //for(int i=0;i<n;i++)
    //    cout<<x[i]-x2[i]<<endl;
}


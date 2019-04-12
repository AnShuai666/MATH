/*
 * 日期:	2018-12-1
 * 时间:	16:15
 * 姓名:
 * 邮箱:
*/
#include "Matrix/matrix_svd.hpp"
int main()
{
    int m=6;int n=5;
    double arr[35]={11,2,23,4,45,6,5,8,9,10,45,12,23,3,4,25,2,55,2,3,3,5,11,2,3,53,52,5,2,5,33,22,55,33,0};
    double U[30]={0};
    double S[5]={0};
    double Vt[25]={0};
    math::matrix::svd_decomposition<double>(arr,m,n,U,S,Vt);

    return 0;
}
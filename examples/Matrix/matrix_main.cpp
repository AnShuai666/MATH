#include "MATH/Matrix/matrix_svd.hpp"
#include "MATH/Matrix/matrix.hpp"
#include "MATH/Matrix/matrix_LU.hpp"
#include<iostream>
using namespace std;

const int n =3;
//矩阵的ALU分解

int main() {
    float H[9]={-0.00044807,-0.000176254,3.33749e-05,-0.000176254,6.58222e-06,-1.80263e-05,3.33749e-05,-1.80263e-05,5.38546e-05};
    float dD[3]={-0.000366091,1.19677e-05,1.87893e-05,};
    float X[3]={};
    LUPSolve(H,dD,X,n);
    for(int i=0;i<3;i++)
        cout<<X[i]<<endl;
}
#include "MATH/Matrix/matrix.hpp"
//#include "Matrix/matrix_qr.hpp"
int main2()
{
    //Matrix<int,3,3> matrix1(3);
   // Matrix<int,3,3> matrixQ;
    //Matrix<int,3,3> matrixR;
    //qr_decomposition(&matrix1,&matrixQ,&matrixR);
    return 0;
}

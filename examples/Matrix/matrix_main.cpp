#include "MATH/Matrix/matrix_svd.hpp"
#include "MATH/Matrix/matrix.hpp"
#include "MATH/Matrix/matrix_lu.hpp"
#include<iostream>
using namespace std;

const int n =3;
//矩阵的ALU分解

int main() {
    float H[16]={-0.00044807,-0.000176254,3.33749,-0.000176254,6.58222,-1.80263,3.33749,-1.80263,5.38546,-0.00044807,-0.000176254,3.33749,-0.000176254,6.58222,-1.80263,3.33749};
    float dD[4]={-0.000366091,1.19677,1.87893,1.87893};
    float X[4]={};
    Matrix<float ,4,4> matrix(H);
    cout<<matrix.determiniant()<<endl;
    cout<<matrix.inverse()<<endl;
    lupSolve(H,dD,X,n);
    for(int i=0;i<4;i++)
        cout<<X[i]<<endl;
    Matrix<float,5,5> matrix1;
    matrix1.setIdentity();
    cout<<matrix1<<endl;
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

//
// Created by doing on 19-6-5.
//

//这两个宏必须要 我也不知道为什么
#define BOOST_AUTO_TEST_MAIN
#define BOOST_TEST_DYN_LINK

#include <boost/test/unit_test.hpp>
#include <iostream>
#include "MATH/Matrix/matrix.hpp"
#include <opencv2/opencv.hpp>
#include <MATH/Matrix/matrix_cholesky.hpp>
#include <MATH/Matrix/matrix_conjugate_gradient.hpp>
#include <MATH/Matrix/matrix_svd.hpp>
using namespace cv;
using namespace math;

BOOST_AUTO_TEST_SUITE(matrix_test)

    BOOST_AUTO_TEST_CASE(lup_slove)
    {
        float H[16]={-0.00044807,-0.000176254,3.33749,-0.000176254,6.58222,-1.80263,3.33749,-1.80263,5.38546,-0.00044807,-0.000176254,3.33749,-0.000176254,6.58222,-1.80263,3.33749};
        float dD[4]={-0.000366091,1.19677,1.87893,1.87893};
        float X[4]={};
        int n=4;
        Matrix<float ,4,4> matrix(H);
        lupSolve(H,dD,X,n);
        Mat mat_X(4,1,CV_32FC1,X);
        Mat mat(4,4,CV_32FC1,H);
        Mat mat_b(4,1,CV_32FC1,dD);

        Mat mat_inv=mat.inv();
        Mat mat_x=mat_inv*mat_b;
        Mat mat_sub=abs(mat_X-mat_x);
        cout<<mat_sub<<endl;
        cout<<sum(mat_sub)[0]<<endl;
        BOOST_CHECK( sum(mat_sub)[0] < 0.01);
    }
    BOOST_AUTO_TEST_CASE(lu_slove)
    {
        float H[16]={-0.00044807,-0.000176254,3.33749,-0.000176254,6.58222,-1.80263,3.33749,-1.80263,5.38546,-0.00044807,-0.000176254,3.33749,-0.000176254,6.58222,-1.80263,3.33749};
        float dD[4]={-0.3,1.19677,1.87893,1.87893};
        float X[4]={};
        int n=4;
        Matrix<float ,4,4> matrix(H);
        luSolve(H,dD,X,n);
        Mat mat_X(4,1,CV_32FC1,X);
        Mat mat(4,4,CV_32FC1,H);
        Mat mat_b(4,1,CV_32FC1,dD);
        //for(int i=0;i<4;i++)
        //    cout<<X[i]<<endl;
        Mat mat_inv=mat.inv();
        Mat mat_x=mat_inv*mat_b;
        Mat mat_sub=abs(mat_X-mat_x);
        cout<<mat_sub<<endl;
        cout<<sum(mat_sub)[0]<<endl;
        BOOST_CHECK( sum(mat_sub)[0] < 0.01);
    }
    BOOST_AUTO_TEST_CASE(inverse)
    {
        float H[16]={-0.00044807,-0.000176254,3.33749,-0.000176254,6.58222,-1.80263,3.33749,-1.80263,5.38546,-0.00044807,-0.000176254,3.33749,-0.000176254,6.58222,-1.80263,3.33749};
        Matrix<float ,4,4> matrix(H);
        Matrix<float ,4,4> matrix_inv = matrix.inverse();

        Mat mat_matrix_inv(4,4,CV_32FC1,*matrix_inv);
        Mat mat(4,4,CV_32FC1,H);
        Mat mat_inv=mat.inv();

        Mat mat_sub=abs(mat_matrix_inv-mat_inv);
        cout<<mat_sub<<endl;
        cout<<sum(mat_sub)[0]<<endl;
        BOOST_CHECK( sum(mat_sub)[0] < 0.01);
    }
    BOOST_AUTO_TEST_CASE(determinant_test)
    {
        float H[16]={-0.00044807,-0.000176254,3.33749,-0.000176254,6.58222,-1.80263,3.33749,-1.80263,5.38546,-0.00044807,-0.000176254,3.33749,-0.000176254,6.58222,-1.80263,3.33749};
        Matrix<float ,4,4> matrix(H);
        float det_matrix=matrix.determiniant();

        Mat mat(4,4,CV_32FC1,H);
        float det_mat=determinant(mat);
        float sub= abs(det_mat-det_matrix);
        cout<<sub<<endl;
        BOOST_CHECK( sub < 0.01);
    }
    BOOST_AUTO_TEST_CASE(conjugate)
    {
        const int n=3;
        float *H=new float[n*n];
        float *b=new float[n];
        double *x=new double[n];
        for(int i=0;i<n;i++)
        {
            for(int j=i;j<n;j++) {
                H[i*n+j] = (rand() % 100) / 10.f;
                H[j*n+i]=H[i*n+j];
            }
        }
        for(int i=0;i<n;i++)
            b[i]=(rand()%100)/10.f;
        float err=  conjugateGradient(H,b,x,n);
        cout<<err<<endl;
        BOOST_CHECK(err<0.01);
    }
    BOOST_AUTO_TEST_CASE(cholesky)
    {
        const int n=3;
        float *H=new float[n*n]{  1   ,  2   ,  3,
                                  2   ,  8,     8,
                                  3   ,  8 ,   35};
        float *L=new float[n*n];

        Mat mat_h(n,n,CV_32FC1,H);
        cout<<mat_h<<endl;
        choleskyDecomposition(H,n,L);
        Mat mat_l(n,n,CV_32FC1,L);
        cout<<mat_l<<endl;
        Mat mat_lt;
        transpose(mat_l,mat_lt);
        float err=sum(abs(mat_h-mat_l*mat_lt))[0];
        cout<<err<<endl;
        BOOST_CHECK(err<0.01);
    }
    BOOST_AUTO_TEST_CASE(svd)
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
        svdDecomposition(H,U,S,V,row,col,K);
        Mat mats(K,K,CV_32FC1);
        for(int i=0;i<K;i++)
            mats.at<float>(i,i)=S[i];
        Mat matu(row,K,CV_32FC1,U);
        Mat matv(K,col,CV_32FC1,V);
        //transpose(matv,matv);
        Mat mata(row,col,CV_32FC1,H);
        float err=sum(abs(mata-matu*mats*matv))[0];
        cout<<err<<endl;
        BOOST_CHECK(err<0.01);
    }

BOOST_AUTO_TEST_SUITE_END()
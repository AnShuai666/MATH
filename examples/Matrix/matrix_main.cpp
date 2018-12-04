/*
 * 日期:	2018-12-1
 * 时间:	16:15
 * 姓名:
 * 邮箱:
*/

#include <Matrix/matrix.hpp>

using namespace matrix;

int main()
{
    cout<<"sfd"<<endl;
    Matrix<int> matrix1;

    Matrix<float> matrix_f(2,3);
    Matrix<float> matrix_f2(2,3);
    matrix_f.input();
    matrix_f2.input();
    Matrix<float > matrix2(matrix_f);
    cout<<matrix1<<endl;
//    cout<<matrix_f<<endl;
//    cout<<matrix2<<endl;
//    cout<<matrix2+matrix_f<<endl;
//    cout<<matrix2-matrix_f<<endl;
    cout<<matrix2*matrix_f2<<endl;

    return 0;
}


//
// Created by doing on 19-4-19.
//

#include<string.h>
//#define float double
static int DN=0;
//inline float abs(float x){(x)=(x)<0?(-x):(x);
//    return x;}
//LUP分解
bool pbgLupDescomposition(float* A, float* L, float* U, int* P)
{
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
            if (abs( A[j * DN + i]) > p)
            {
                p   = abs(A[j * DN + i]);
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
void pbgLupSolve(float* L, float* U, int* P, float* b,float* x)
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

/*****************矩阵原地转置BEGIN********************/

/* 后继 */
int pbgGetNext(int i, int m, int n)
{
    return (i % n) * m + i / n;
}

/* 前驱 */
int pbgGetPre(int i, int m, int n)
{
    return (i % m) * n + i / m;
}

/* 处理以下标i为起点的环 */
void pbgMovedata(float *mtx, int i, int m, int n)
{
    float temp = mtx[i]; // 暂存
    int   cur = i;    // 当前下标
    int   pre = pbgGetPre(cur, m, n);
    while(pre != i)
    {
        mtx[cur] = mtx[pre];
        cur = pre;
        pre = pbgGetPre(cur, m, n);
    }
    mtx[cur] = temp;
}

/* 转置，即循环处理所有环 */
void pbgTranspose(float *mtx, int m, int n)
{
    for (int i =0; i < m * n; ++i)
    {
        int next = pbgGetNext(i, m, n);

        while(next > i) // 若存在后继小于i说明重复,就不进行下去了（只有不重复时进入while循环）
        {
            next = pbgGetNext(next, m, n);
        }
        if(next == i)  // 处理当前环
        {
            pbgMovedata(mtx, i, m, n);
        }
    }
}
/*****************矩阵原地转置END********************/

//LUP求逆(将每列b求出的各列x进行组装)
template<typename _Tp>
bool pbgLupSolveInverse( _Tp* A,int n,float* inv_A)
{
    DN=n;
    //创建矩阵A的副本，注意不能直接用A计算，因为LUP分解算法已将其改变
    float *_A_mirror   = new float[DN * DN]();
    float *_inv_A_each = new float[DN]();//矩阵逆的各列
    float *_b          =new float[DN]();//b阵为B阵的列矩阵分量

    float *_L = new float[DN * DN]();
    float *_U = new float[DN * DN]();
    int   *_P = new int[DN]();
    bool _des_sucess=false;
    for(int i = 0; i < DN; i++)
    {
        //构造单位阵的每一列
        for(int j = 0; j < DN; j++)
        {
            _b[j] = 0;
        }
        _b[i] = 1;

        //每次都需要重新将A复制一份

        for(int j = 0; j < DN * DN; j++)
        {
            _A_mirror[j] = (float)A[j];
        }
        _des_sucess=pbgLupDescomposition(_A_mirror, _L, _U, _P);
        if(!_des_sucess)
            break;

        pbgLupSolve (_L, _U, _P, _b,_inv_A_each);
        memcpy((float*)inv_A + i * DN, (float*)_inv_A_each, DN * sizeof(float));//将各列拼接起来
    }
    if(_des_sucess)
        pbgTranspose(inv_A, DN, DN);//由于现在根据每列b算出的x按行存储，因此需转置
    else
        memset(inv_A,0,DN*DN);
    delete[] _A_mirror;
    delete[] _inv_A_each;
    delete[] _b;
    delete[] _L;
    delete[] _U;
    delete[] _P;
    return _des_sucess;
}

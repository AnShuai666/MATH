
#include <MATH/flann/flann.hpp>
#include <stdio.h>
#include <iostream>
using namespace std;
using namespace flann;

int main(int argc, char** argv)
{
    int nn = 3;

    printf("run\n");
    Features<float> dataset;
    Features<float> query;

    //load_from_file(dataset, "dataset.hdf5","dataset");
    //load_from_file(query, "dataset.hdf5","query");
    int m=10000,n=32;
    float* data=new float[m*n];
    float* que=new float[m*n];
    int* res=new int[m*n];
    for(int i=0;i<m;i++)
    {
        res[i]=random()%m;
    }
    for(int i=0;i<m;i++)
    {
        for(int j=0;j<n;j++)
        {
            data[i*n+j]=(float)(random()%100)/10;
        }
    }
    for(int i=0;i<m;i++)
    {
        for(int j=0;j<n;j++)
        {
            que[i*n+j]=data[res[i]*n+j];
        }
    }
    dataset=Features<float>(data,m,n);
    query=Features<float>(que,m,n);
    Features<int> indices(new int[query.rows*nn], query.rows, nn);
    Features<float> dists(new float[query.rows*nn], query.rows, nn);



    // do a knn search, using 128 checks
    clock_t start,end,total;
    start=clock();
    // construct an randomized kd-tree index using 4 kd-trees
    Index<L2<float> > index(dataset, flann::HierarchicalClusteringIndexParams());
    index.buildIndex();
    index.knnSearch(query, indices, dists, nn, flann::SearchParams(128));
    end=clock();
    total=end-start;
    cout<<"run time = "<<(double)total/CLOCKS_PER_SEC*1000<<"ms"<<endl;
    for(int i=0;i<m;i++)
    {
        if(indices[i][0]!=res[i]) {
            cout << res[i] << " ";
            for (int j = 0; j < 1; j++) {
                cout << indices[i][j] << " ";
                cout << dists[i][j] << "; ";
            }
            cout << endl;
        }
    }
    //flann::save_to_file(indices,"result.hdf5","result");


    delete[] dataset.ptr();
    delete[] query.ptr();
    delete[] indices.ptr();
    delete[] dists.ptr();
    
    return 0;
}

//
// Created by doing on 19-6-6.
//

//这两个宏必须要 我也不知道为什么
#define BOOST_AUTO_TEST_MAIN
#define BOOST_TEST_DYN_LINK

#include <boost/test/unit_test.hpp>
#include <iostream>
#include "MATH/Matrix/vector.hpp"
#include "MATH/Flann/flann.hpp"
using namespace flann;

BOOST_AUTO_TEST_SUITE(flann_test)

    //第七个构造函数
    BOOST_AUTO_TEST_CASE(flann)
    {
        int nn = 1;

        printf("run\n");
        //Features<float> dataset;
        //Features<float> query;

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
        Features<float> dataset=Features<float>(data,m,n);
        Features<float>query =Features<float>(que,m,n);

        Features<int> indices(new int[query.rows*nn], query.rows, nn);
        Features<float> dists(new float[query.rows*nn], query.rows, nn);



        // do a knn search, using 128 checks
        clock_t start,end,total;
        start=clock();
        // construct an randomized kd-tree index using 4 kd-trees
        Index<L2<float> > index(dataset, HierarchicalClusteringIndexParams());
        index.buildIndex();
        index.knnSearch(query, indices, dists, nn, SearchParams(128));
        end=clock();
        total=end-start;
        cout<<"run time = "<<(double)total/CLOCKS_PER_SEC*1000<<"ms"<<endl;
        int error_count=0;
        for(int i=0;i<m;i++)
        {
            if(indices[i][0]!=res[i])
            {
                error_count++;
                cout << res[i] << " ";
                for (int j = 0; j < 1; j++) {
                    cout << indices[i][j] << " ";
                    cout << dists[i][j] << "; ";
                }
                cout << endl;
            }
        }
        delete[] dataset.ptr();
        delete[] query.ptr();
        delete[] indices.ptr();
        delete[] dists.ptr();
        BOOST_CHECK(error_count==0);
    }

BOOST_AUTO_TEST_SUITE_END()

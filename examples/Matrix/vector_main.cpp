//
// Created by AnShuai on 18-12-10.
//

#include <iostream>
#include "Matrix/vector.hpp"

using namespace std;


int main()
{
    cout<<"debug start"<<endl;
    math::matrix::Vector2f vector2f_1(1.3,2.5);
    math::matrix::Vector2f vector2f_2 = vector2f_1;
    math::matrix::Vector2d vector2d_1 = vector2f_1;
    
    math::matrix::Vector3f vector3f(vector2f_1,1);
    cout<<vector3f<<endl;
    return 0;
}


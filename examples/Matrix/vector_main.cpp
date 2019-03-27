//
// Created by AnShuai on 18-12-10.
//

#include <iostream>
#include "Matrix/vector.hpp"

using namespace std;


int main()
{
    cout<<"debug start"<<endl;
    matrix::Vector2f vector2f_1(1.3,2.5);
    matrix::Vector2f vector2f_2 = vector2f_1;
    matrix::Vector2d vector2d_1 = vector2f_1;
    cout<<vector2d_1<<endl;
    return 0;
}


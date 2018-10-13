#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include "../include/matrix.h"

using namespace Matrix;

int main(int argc, char *argv[])
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
    // auto m = Matrix::Matrix::getE(4);

    // m->info(); 
    
    // auto m1 =  Matrix::Matrix::trans(*m);
    
    // m1->info();
    // m1->info();

    // Matrix::Matrix(2,3,1).info();
    // Matrix::Matrix::trans(Matrix::Matrix(3,2,1))->info();

    // Matrix::Matrix m(1,1,1);

    // cout << m.info() << endl;
    return 0;
}

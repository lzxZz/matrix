#include <gtest/gtest.h>
#include "../include/matrix.h"


TEST(InfoTest, Test)
{
    Matrix::Matrix mat(1,2,0);
    
    EXPECT_EQ("Matrix:(1,2)\n[0,0,]\n", mat.info()); 


    EXPECT_EQ("Matrix:(2,2)\n[1,1,]\n[1,1,]\n", Matrix::Matrix(2,2,1).info()); 

    
}

TEST(EMatrixTest,TEST)
{
    EXPECT_EQ("Matrix:(1,1)\n[1,]\n",Matrix::Matrix::getE(1).info());

    EXPECT_EQ("Matrix:(2,2)\n[1,0,]\n[0,1,]\n",Matrix::Matrix::getE(2).info());

}
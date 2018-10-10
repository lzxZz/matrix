#include <gtest/gtest.h>
#include "../include/matrix.h"


TEST(InfoTest, Test)
{
    Matrix::Matrix mat(1,2,0);
    
    EXPECT_EQ("Matrix:(1,2)\n[0,0,]\n", mat.info()); 


    EXPECT_EQ("Matrix:(2,2)\n[1,1,]\n[1,1,]\n", Matrix::Matrix(2,2,1).info()); 

    
}

TEST(EMatrixTest,Test)
{
    EXPECT_EQ("Matrix:(1,1)\n[1,]\n",Matrix::Matrix::getE(1).info());

    EXPECT_EQ("Matrix:(2,2)\n[1,0,]\n[0,1,]\n",Matrix::Matrix::getE(2).info());

}

TEST(MultiTest,Test)
{
    EXPECT_EQ("Matrix:(1,1)\n[20,]\n",
        Matrix::Matrix::getE(1).multi_number(20).info());

    EXPECT_EQ("Matrix:(1,1)\n[0.5,]\n",
        Matrix::Matrix::getE(1).multi_number(0.5).info());


    EXPECT_EQ("Matrix:(1,1)\n[-20,]\n",
        Matrix::Matrix::getE(1).multi_number(-20).info());

    EXPECT_EQ("Matrix:(1,1)\n[-0.5,]\n",
        Matrix::Matrix::getE(1).multi_number(-0.5).info());

    
    EXPECT_EQ("Matrix:(2,2)\n[0,0,]\n[0,0,]\n", 
        Matrix::Matrix(2,2,1).multi_number(0).info()); 

    EXPECT_EQ("Matrix:(2,2)\n[12.3,12.3,]\n[12.3,12.3,]\n", 
        Matrix::Matrix(2,2,1).multi_number(12.3).info()); 
}

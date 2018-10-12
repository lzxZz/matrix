#include <gtest/gtest.h>
#include "../include/matrix.h"


TEST(InfoTest, Test)
{
    Matrix::Matrix mat(1,2,0);
    
    EXPECT_EQ("Matrix:(1,2)\n[0,0,]\n", mat.info()); 


    EXPECT_EQ("Matrix:(2,2)\n[1,1,]\n[1,1,]\n", 
        Matrix::Matrix(2,2,1).info()); 

    
}

TEST(EMatrixTest,Test)
{
    EXPECT_EQ("Matrix:(1,1)\n[1,]\n",
        Matrix::Matrix::getE(1).info());

    EXPECT_EQ("Matrix:(2,2)\n[1,0,]\n[0,1,]\n",
        Matrix::Matrix::getE(2).info());

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

TEST(SubTest,Test)
{
    Matrix::Matrix m1(2,2,3);
    Matrix::Matrix m2(2,2,1);
    
    EXPECT_EQ(Matrix::Matrix(2,2,2).info(),
        Matrix::Matrix::sub(m1,m2).info());
}

TEST(AddTest,Test)
{
    Matrix::Matrix m1(2,2,2);
    Matrix::Matrix m2(2,2,1);
    
    EXPECT_EQ(Matrix::Matrix(2,2,3).info(),
        Matrix::Matrix::add(m1,m2).info());
}

TEST(MultiMatrixTest,ErrorMultiTest)
{
    Matrix::Matrix m1(2,2,1);
    Matrix::Matrix m2(1,2,1);
    Matrix::Matrix m3(2,1,1);

    Matrix::Matrix empty(0,0,0);
    EXPECT_EQ(empty.info(), Matrix::Matrix::multi_matrix(m1,m2).info());
    EXPECT_EQ(empty.info(), Matrix::Matrix::multi_matrix(m3,m1).info());
    
}

//测试单位矩阵的乘法
TEST(MultiMatrixTest,EMultiTest)
{
    Matrix::Matrix m1(2,2,1);
    Matrix::Matrix m2(1,2,1);
    Matrix::Matrix m3(2,1,1);

    Matrix::Matrix e1 = Matrix::Matrix::getE(1);
    Matrix::Matrix e2 = Matrix::Matrix::getE(2);

    EXPECT_EQ(m1.info(), Matrix::Matrix::multi_matrix(m1,e2).info());
    EXPECT_EQ(m2.info(), Matrix::Matrix::multi_matrix(m2,e2).info());
    EXPECT_EQ(m3.info(), Matrix::Matrix::multi_matrix(m3,e1).info());

}

TEST(MultiMatrixTest,GeneralTest)
{
    Matrix::Matrix m1(2,2,1);
    Matrix::Matrix m2(1,2,1);
    Matrix::Matrix m3(2,1,1);

    
    EXPECT_EQ(Matrix::Matrix(2,2,2).info(),
        Matrix::Matrix::multi_matrix(m1,m1).info());

    EXPECT_EQ(Matrix::Matrix(1,1,2).info(),
        Matrix::Matrix::multi_matrix(m2,m3).info());
}

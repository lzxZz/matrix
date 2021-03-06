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
        Matrix::Matrix::getE(1)->info());

    EXPECT_EQ("Matrix:(2,2)\n[1,0,]\n[0,1,]\n",
        Matrix::Matrix::getE(2)->info());

}

TEST(MultiTest,Test)
{
    EXPECT_EQ("Matrix:(1,1)\n[20,]\n",
        Matrix::Matrix::getE(1)->multi_number(20).info());

    EXPECT_EQ("Matrix:(1,1)\n[0.5,]\n",
        Matrix::Matrix::getE(1)->multi_number(0.5).info());


    EXPECT_EQ("Matrix:(1,1)\n[-20,]\n",
        Matrix::Matrix::getE(1)->multi_number(-20).info());

    EXPECT_EQ("Matrix:(1,1)\n[-0.5,]\n",
        Matrix::Matrix::getE(1)->multi_number(-0.5).info());

    
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
        Matrix::Matrix::sub(m1,m2)->info());
}

TEST(AddTest,Test)
{
    Matrix::Matrix m1(2,2,2);
    Matrix::Matrix m2(2,2,1);
    
    EXPECT_EQ(Matrix::Matrix(2,2,3).info(),
        Matrix::Matrix::add(m1,m2)->info());
}

TEST(MultiMatrixTest,ErrorMultiTest)
{
    Matrix::Matrix m1(2,2,1);
    Matrix::Matrix m2(1,2,1);
    Matrix::Matrix m3(2,1,1);

    Matrix::Matrix empty(0,0,0);
    EXPECT_EQ(empty.info(), Matrix::Matrix::multi_matrix(m1,m2)->info());
    EXPECT_EQ(empty.info(), Matrix::Matrix::multi_matrix(m3,m1)->info());
    
}

//测试单位矩阵的乘法
TEST(MultiMatrixTest,EMultiTest)
{
    Matrix::Matrix m1(2,2,1);
    Matrix::Matrix m2(1,2,1);
    Matrix::Matrix m3(2,1,1);

    auto e1 = Matrix::Matrix::getE(1);
    auto e2 = Matrix::Matrix::getE(2);

    EXPECT_EQ(m1.info(), Matrix::Matrix::multi_matrix(m1,*e2)->info());
    EXPECT_EQ(m2.info(), Matrix::Matrix::multi_matrix(m2,*e2)->info());
    EXPECT_EQ(m3.info(), Matrix::Matrix::multi_matrix(m3,*e1)->info());

}

TEST(MultiMatrixTest,GeneralTest)
{
    Matrix::Matrix m1(2,2,1);
    Matrix::Matrix m2(1,2,1);
    Matrix::Matrix m3(2,1,1);

    
    EXPECT_EQ(Matrix::Matrix(2,2,2).info(),
        Matrix::Matrix::multi_matrix(m1,m1)->info());

    EXPECT_EQ(Matrix::Matrix(1,1,2).info(),
        Matrix::Matrix::multi_matrix(m2,m3)->info());
}

TEST(VectorTest,generateTest)
{
    Matrix::Matrix v1(10,1,0);
    v1.set_value(3,0,1);
    EXPECT_EQ(v1.info(),Matrix::Matrix::getIVector(10,3)->info());
}

TEST(TransTest,Test)
{
    auto m = Matrix::Matrix::getE(4);

    EXPECT_EQ(m->info(), Matrix::Matrix::trans(*m)->info());

    EXPECT_EQ(Matrix::Matrix(2,3,1).info(), Matrix::Matrix::trans(Matrix::Matrix(3,2,1))->info());

}

TEST(GetRowTest,ErrorTest)
{
    Matrix::Matrix m(5,5,1);

    EXPECT_EQ(Matrix::Matrix(0,0,0).info(), m.get_row(5)->info());
    EXPECT_EQ(Matrix::Matrix(0,0,0).info(), m.get_row(20)->info());
}

TEST(GetRowTest,NormalTest)
{
    Matrix::Matrix m(5,4,1);

    EXPECT_EQ(Matrix::Matrix(1,4,1).info(), m.get_row(4)->info());
}



// TEST(SetRowTest,ErrorTest)
// {
//     Matrix::Matrix m(5,1,1);
    
//     EXPECT_EQ(Matrix::Matrix(0,0,0).info(), 
//         m.set_row(5,Matrix::Matrix(1,1,1))->info());
//     EXPECT_EQ(Matrix::Matrix(0,0,0).info(), 
//         m.set_row(20,Matrix::Matrix(1,1,1))->info());
// }

TEST(SetRowTest,NormalTest)
{
    Matrix::Matrix m(5,4,1);
    m.set_value(4,1,20);

    Matrix::Matrix row = Matrix::Matrix(1,4,1);


    EXPECT_EQ(m.info(), m.set_row(4,row).info());
}



TEST(GetColTest,ErrorTest)
{
    Matrix::Matrix m(5,5,1);

    EXPECT_EQ(Matrix::Matrix(0,0,0).info(), m.get_col(5)->info());
    EXPECT_EQ(Matrix::Matrix(0,0,0).info(), m.get_col(20)->info());
}

TEST(GetColTest,NormalTest)
{
    Matrix::Matrix m(5,4,1);
    

    EXPECT_EQ(Matrix::Matrix(5,1,1).info(), m.get_col(0)->info());
}



// TEST(SetColTest,ErrorTest)
// {
//     Matrix::Matrix m(5,1,1);
    

//     EXPECT_EQ(Matrix::Matrix(0,0,0).info(), 
//         m.set_col(1,Matrix::Matrix::getIVector(5,3)).info());
//     EXPECT_EQ(Matrix::Matrix(0,0,0).info(), 
//         m.set_col(20,Matrix::Matrix::getIVector(5,3)).info());

// }

TEST(SetColTest,NormalTest)
{
    Matrix::Matrix m(5,4,0);
    m.set_value(4,1,1);

    EXPECT_EQ(m.info(), 
        m.set_row(4,*Matrix::Matrix::getIVector(5,4)).info());
}

TEST(VectorInitTest, Test)
{
    EXPECT_EQ(Matrix::Matrix::getIVector(3,1)->info(),
        Matrix::Matrix::trans(Matrix::Matrix(vector<double>{0,1,0}))->info());
}
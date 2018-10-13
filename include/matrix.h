
#ifndef __MATRIX_H
#define __MATRIX_H

#include <iostream>
#include <string>
#include <sstream>
#include <memory>
#include <vector>
#include <cassert>
using namespace std;

namespace Matrix
{


class Matrix
{
    static Matrix *empty_matrix;
    enum class Vector_Direction{
        Horizontal,
        Vectical
    };
    using Vector = Matrix;
  public:
    Matrix(size_t r, size_t c) : row_count(r), col_count(c)
    {
        values = new double[r * c];
    }

    Matrix(size_t r, size_t c, double init_value) : row_count(r), col_count(c)
    {
        values = new double[r * c];
        for (size_t i = 0; i < row_count; i++)
        {
            for (size_t j = 0; j < col_count; j++)
            {
                set_value(i, j, init_value);
            }
        }
    }

    Matrix(std::vector<double> vec)
    {
        row_count = 1;
        col_count = vec.size();
        values = new double[row_count * col_count];
        for (size_t i = 0; i < col_count; i++)
        {
            set_value(0,i,vec.at(i));
        }
    }

    //打印的时候每一行最后都有一个多余的逗号
    string info()
    {
        stringstream os;

        os << "Matrix:"
           << "(" << row_count << "," << col_count << ")" << endl;

        for (size_t i = 0; i < row_count; i++)
        {
            os << "[";
            for (size_t j = 0; j < col_count; j++)
            {
                os << get_value(i, j) << ",";
            }
            
         
            os << "]" << endl;
        }

        return os.str();
    }

    double get_value(int r, int c) const
    {
        return *(values + r * col_count + c);
    }
    void set_value(int r, int c, double v)
    {
        *(values + r * col_count + c) = v;
    }
    Matrix &multi_number(double number)
    {
        for (size_t i = 0; i < row_count; i++)
        {
            for (size_t j = 0; j < col_count; j++)
            {
                set_value(i, j, get_value(i,j) * number);
            }
        }
        return *this;
    }
    //返回一个新矩阵的引用,使用的时候使用智能指针,否则会泄露
    static shared_ptr<Matrix> sub(const Matrix &m1, const Matrix &m2)
    {
        assert(m1.col_count == m2.col_count);
        assert(m1.row_count == m2.row_count);

        shared_ptr<Matrix> m = make_shared<Matrix>(m1.row_count,m1.col_count);

        for (int i = 0; i < m1.row_count; i++)
        {
            for (int j = 0; j < m1.col_count; j++)
            {
                m->set_value(i,j, m1.get_value(i,j) - m2.get_value(i,j));
            }
        }

        return m;
    }

    //返回一个新矩阵的引用,使用的时候使用智能指针,否则会泄露
    static shared_ptr<Matrix> add(const Matrix &m1, const Matrix &m2)
    {
        assert(m1.col_count == m2.col_count);
        assert(m1.row_count == m2.row_count);

        shared_ptr<Matrix> m = make_shared<Matrix>(m1.row_count,m1.col_count);

        for (int i = 0; i < m1.row_count; i++)
        {
            for (int j = 0; j < m1.col_count; j++)
            {
                m->set_value(i,j, m1.get_value(i,j) + m2.get_value(i,j));
            }
        }

        return m;
    }

    static shared_ptr<Matrix> multi_matrix(const Matrix &m1, const Matrix &m2)
    {
        if (m1.col_count != m2.row_count)
        {
            return make_shared<Matrix>(0,0,0);
        }

        shared_ptr<Matrix> m = make_shared<Matrix>(m1.row_count,m2.col_count,0);
        for (size_t i = 0; i < m->row_count; i++)
        {
            for (size_t j = 0; j < m->col_count; j++)
            {
                double value = 0;
                for (size_t k = 0; k < m1.col_count; k ++)
                {
                    value += m1.get_value(i,k) * m2.get_value(k,j);
                }
                m->set_value(i,j,value);
            }
        }
        return m; 
    }

    static shared_ptr<Matrix>  trans(const Matrix &m)
    {
        shared_ptr<Matrix>  mat =  make_shared<Matrix>(m.col_count,m.row_count);

        for (size_t i = 0; i < m.row_count; i++)
        {
            for (size_t j = 0; j < m.col_count; j++)
            {
                mat->set_value(j,i,m.get_value(i,j));
            }
        }
        
        return mat;
    }

    static shared_ptr<Matrix> getIVector(size_t dim, size_t index, Vector_Direction direc = Vector_Direction::Vectical)
    {
        shared_ptr<Matrix> m;
        if (direc == Vector_Direction::Vectical)
        {
            m = make_shared<Matrix>(dim,1,0);
            m->set_value(index,0,1);
        }
        else
        {
            m = make_shared<Matrix>(1,dim,0);
            m->set_value(0,index,1);
        }
        
        return m;
    }

    //返回一个新矩阵的引用,使用的时候使用智能指针,否则会泄露
    static  shared_ptr<Matrix> getE(size_t dim)
    {
        shared_ptr<Matrix> m = make_shared<Matrix>(dim,dim,0);

        for (size_t i = 0; i < dim; i++)
        {
            m->set_value(i,i,1);
        }

        return m;
    }

    shared_ptr<Matrix> get_row(size_t row_index)
    {
        if (row_index >= this->row_count)
        {
            
            return make_shared<Matrix>(0,0,0);
        }
        shared_ptr<Vector> vec = make_shared<Vector>(1,this->col_count);
        for (size_t i = 0; i < col_count; i++)
        {
            vec->set_value(0,i,get_value(row_index, i));
        }
        return vec;
    }

    
    Matrix &set_row(size_t index,const Vector &row)
    {
        if (index >= this->row_count)
        {   
            // return make_shared<Matrix>(0,0,0);
            throw (out_of_range("矩阵维度溢出"));
        }
        
        for (size_t i = 0; i < col_count; i++)
        {
            this->set_value(index,i, row.get_value(0,i));
        }

        return *this;
    }

    shared_ptr<Matrix> get_col(size_t index)
    {
        if (index >= this->col_count)
        {
            return make_shared<Matrix>(0,0,0);
        }
        shared_ptr<Vector> vec = make_shared<Vector>(this->row_count,1);
        
        for (size_t i = 0; i < row_count; i++)
        {
            vec->set_value(i,0,get_value(i,index));
        }
        return vec;

    }

    Matrix &set_col(size_t index, Vector col)
    {
        if (index >= this->col_count)
        {
            throw (out_of_range("矩阵维度溢出"));
        }
      
         for (size_t i = 0; i < row_count; i++)
        {
            this->set_value(i,index, col.get_value(i,0));
        }
        return *this;

    }

    ~Matrix(){
        delete [] values;
    }
  private:
    size_t row_count;
    size_t col_count;
    double *values;
};



} // namespace Matrix


#endif
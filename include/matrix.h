
#include <iostream>
#include <string>
#include <sstream>
using namespace std;

namespace Matrix
{

class Matrix
{
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

    double get_value(int r, int c)
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
    static Matrix &sub(Matrix m1, Matrix m2)
    {
        assert(m1.col_count == m2.col_count);
        assert(m1.row_count == m2.row_count);

        Matrix *m = new Matrix(m1.row_count,m1.col_count);

        for (int i = 0; i < m1.row_count; i++)
        {
            for (int j = 0; j < m1.col_count; j++)
            {
                m->set_value(i,j, m1.get_value(i,j) - m2.get_value(i,j));
            }
        }

        return *m;
    }

    //返回一个新矩阵的引用,使用的时候使用智能指针,否则会泄露
    static Matrix &add(Matrix m1, Matrix m2)
    {
        assert(m1.col_count == m2.col_count);
        assert(m1.row_count == m2.row_count);

        Matrix *m = new Matrix(m1.row_count,m1.col_count);

        for (int i = 0; i < m1.row_count; i++)
        {
            for (int j = 0; j < m1.col_count; j++)
            {
                m->set_value(i,j, m1.get_value(i,j) + m2.get_value(i,j));
            }
        }

        return *m;
    }

    static Matrix &multi_matrix(Matrix m1, Matrix m2)
    {
        if (m1.col_count != m2.row_count)
        {
            Matrix *empty = new Matrix(0,0,0);
            return *empty;
        }

        Matrix *m = new Matrix(m1.row_count,m2.col_count,0);
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
        return *m; 
    }

    static Matrix &trans(Matrix m)
    {
        Matrix *mat = new Matrix(m.col_count,m.row_count);

        for (size_t i = 0; i < m.row_count; i++)
        {
            for (size_t j = 0; j < m.col_count; j++)
            {
                mat->set_value(j,i,m.get_value(i,j));
            }
        }

        return *mat;
    }

    static Vector &getIVector(size_t dim, size_t index)
    {
        Matrix *m = new Matrix(dim,1,0);
        m->set_value(index,0,1);
        return *m;
    }

    //返回一个新矩阵的引用,使用的时候使用智能指针,否则会泄露
    static Matrix &getE(size_t dim)
    {
        Matrix *m = new Matrix(dim,dim,0);

        for (size_t i = 0; i < dim; i++)
        {
            m->set_value(i,i,1);
        }

        return *m;
    }

    Vector &get_row(size_t row_index)
    {
        if (row_index >= this->row_count)
        {
            return *(new Matrix(0,0,0));
        }
        Vector *vec = new Vector(1,this->col_count);
        for (size_t i = 0; i < col_count; i++)
        {
            vec->set_value(0,i,get_value(row_index, i));
        }
        return *vec;
    }

    Matrix &set_row(size_t index, Vector row)
    {
        if (index >= this->row_count)
        {
            return *(new Matrix(0,0,0));
        }
        
        for (size_t i = 0; i < col_count; i++)
        {
            this->set_value(index,i, row.get_value(0,i));
        }

        return *this;
    }

  private:
    size_t row_count;
    size_t col_count;
    double *values;
};



} // namespace Matrix
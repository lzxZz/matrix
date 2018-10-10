
#include <iostream>
#include <string>
#include <sstream>
using namespace std;

namespace Matrix
{

class Matrix
{
  public:
    Matrix(size_t r, size_t c) : row_count(r), col_count(r)
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

    static Matrix sub(Matrix m1, Matrix m2)
    {
        assert(m1.col_count == m2.col_count);
        assert(m1.row_count == m2.row_count);

        Matrix m(m1.row_count,m1.col_count);

        for (int i = 0; i < m1.row_count; i++)
        {
            for (int j = 0; j < m1.col_count; j++)
            {
                m.set_value(i,j, m1.get_value(i,j) - m2.get_value(i,j));
            }
        }

        return m;
    }

    static Matrix add(Matrix m1, Matrix m2)
    {
        assert(m1.col_count == m2.col_count);
        assert(m1.row_count == m2.row_count);

        Matrix m(m1.row_count,m1.col_count);

        for (int i = 0; i < m1.row_count; i++)
        {
            for (int j = 0; j < m1.col_count; j++)
            {
                m.set_value(i,j, m1.get_value(i,j) + m2.get_value(i,j));
            }
        }

        return m;
    }
    static Matrix &getE(size_t dim)
    {
        Matrix *m = new Matrix(dim,dim,0);

        for (size_t i = 0; i < dim; i++)
        {
            m->set_value(i,i,1);
        }

        return *m;
    }
  private:
    size_t row_count;
    size_t col_count;
    double *values;
};

using Vector = Matrix;

} // namespace Matrix
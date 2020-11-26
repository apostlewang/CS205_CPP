#include<iostream>
using namespace std;
class Matrix
{
private:
    /* data */
    int num_rows;
    int num_columns;
    float * data;
    int *refcount;

public:
    Matrix(int num_rows, int num_columns, float* data);
    Matrix(const Matrix &m);
    ~Matrix();
    Matrix operator* (const Matrix &m) const;
    Matrix operator* (const float a) const;
    Matrix& operator= (const Matrix &m);
    float operator() (int row, int column) const;
    friend Matrix operator* (const float a,const Matrix &m);  
    friend ostream& operator<<(ostream &os,const Matrix &m);
    friend float* multiMatrix(const Matrix &a, const Matrix &b);
};




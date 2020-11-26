#include"Matrix.hpp"
#include<iostream>
#include<iomanip>
#include <cassert>
using namespace std;

float* multiMatrix(const Matrix &a, const Matrix &b){
    assert (a.num_columns == b.num_rows);
    float* result = new float[b.num_columns*a.num_rows];
    for(int i=0 ; i<a.num_rows; i++){     
        for(int k=0 ; k<a.num_columns; k++){
            float s = a.data[i*a.num_columns+k];                
            for(int j=0 ; j<b.num_columns; j++){
                result[i*b.num_columns+j] += s*b.data[k*b.num_columns+j];
            }
        }         
    }

    return result;
}

Matrix::Matrix(int num_rows, int num_columns, float* data){
    this->num_columns = num_columns;
    this->num_rows = num_rows;
    this->data = data;
    this->refcount = new int(0);
}

Matrix::Matrix(const Matrix &m){
    this->num_columns = m.num_columns;
    this->num_rows = m.num_rows;
    this->data = m.data;
    this->refcount = m.refcount;
    *refcount += 1;
}

Matrix::~Matrix(){
    if(*refcount == 0){
        delete []data;
    }
    else{
        *refcount -= 1;
    }   
}

Matrix Matrix::operator* (const Matrix &m) const{  
    float* newdata = multiMatrix(*this,m);
    Matrix result = Matrix(num_rows,m.num_columns,newdata);
    return result;
}

Matrix Matrix::operator* (const float a) const{
    float * newdata = new float[num_columns*num_rows];
    for (size_t i = 0; i < num_columns*num_rows; i++)
    {
        newdata[i] = data[i]*a;
    }
    Matrix result = Matrix(num_rows,num_columns,newdata);
    return result;
}

Matrix& Matrix::operator= (const Matrix &m){    
    if (this == &m){
        return *this;
    }
    this->num_columns = m.num_columns;
    this->num_rows = m.num_rows;
    if(this->refcount == 0){
        delete [] this->data;
    }
    else{
        *(this->refcount) -= 1;
    }
    this->refcount = m.refcount;
    *refcount += 1;
    this->data = m.data;
    return *this;
}

float Matrix::operator() (int row, int column) const{
    assert(row < this->num_rows && column < this->num_columns && row >= 0 && column >= 0);      
    return data[row*num_columns+column];
}

Matrix operator* (const float a,const Matrix &m){
    float * newdata = new float[m.num_columns*m.num_rows];
    for (size_t i = 0; i < m.num_columns*m.num_rows; i++)
    {
        newdata[i] = m.data[i]*a;
    }
    Matrix result = Matrix(m.num_rows,m.num_columns,newdata);
    return result;
}

ostream& operator<<(ostream &os,const Matrix &m){
    for (size_t i = 0; i < m.num_rows; i++)
    {
        for (size_t j = 0; j < m.num_columns; j++)
        {
            os << setw(10)<< left << m.data[i*m.num_columns+j];
        }
        os << endl;
    }
    os << endl;
    return os;
}

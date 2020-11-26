#include<iostream>
#include"Matrix.hpp"

using namespace std;

int main(){
    float *a = new float[16];
    for (size_t i = 0; i < 16; i++)
    {
        a[i] = i+1;
    } 
    //矩阵A
    //1，2，3，4
    //5，6，7，8
    //9,10,11,12
    //13,14,15,16
    Matrix A = Matrix(4,4,a);
    //Copy Constructor
    Matrix B = Matrix(A);
    //Reload << operator
    cout << "B:" << endl << B;
    //scalar multiplication (right)
    Matrix C = A*1.2;
    cout << "C:" << endl << C;
    //scalar multiplication (left)
    Matrix D = 0.83*A;
    cout << "D:" << endl << D;
    //Matrix multipication
    cout << "C*D:" << endl << C*D;
    //Reload assignment operator
    C = A;
    cout << "C=A:" << endl << C;
    return 0;
}
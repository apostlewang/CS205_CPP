/*
 * @Date: 2020-12-07 17:04:00
 * @Author: Kang Wang
 * @LastEditors: Kang Wang
 * @LastEditTime: 2020-12-07 18:02:22
 */
#include <iostream>
#include <string>
#include "matrix.h"
using namespace std;
template <typename T1>
void useMatrixTemplate(Matrix<T1>& M, T1 array1[][3], T1 array2[][3]);
int main()
{
    string str1[2][3] =
    {
    {"Congra", "y", "ar"},
    {"alm", "don", "La"}
    };
    string str2[2][3] =
    {
    {"tulations", "ou", "e"},
    {"ost", "e the", "b!"}
    };
    int num1[2][3] =
    {
    {1,2,3},
    {4,5,6}
    };
    int num2[2][3] =
    {
    {6,5,4},
    {3,2,1}
    };
    Matrix<string> stringMatrix(2,3);
    Matrix<int> intMatrix(2,3);
    cout << "\nDemonstrating with string matrix:" << endl;
    useMatrixTemplate(stringMatrix, str1, str2);
    cout << "\nDemonstrating with int matrix:" << endl;
    useMatrixTemplate(intMatrix, num1, num2);
    cout << "\n" << endl;
    return 0;
}
template <typename T1>
void useMatrixTemplate(Matrix<T1>& M, T1 array1[][3], T1 array2[][3])
{
    M.setMatrix(array1);
    cout << "\nMatrix set to first array" << endl;
    M.printMatrix();
    M.addMatrix(array2);
    cout << "\nMatrix incremented by second array" << endl;
    M.printMatrix();
}
/*
 * @Date: 2020-12-07 17:04:47
 * @Author: Kang Wang
 * @LastEditors: Kang Wang
 * @LastEditTime: 2020-12-07 18:05:36
 */
#ifndef CLASSTEMPLATE_MATRIX_H
#define CLASSTEMPLATE_MATRIX_H

#define MAXROWS 5
#define MAXCOLS 5

template<class T>
class Matrix
{
private:
    T matrix[MAXROWS][MAXCOLS];
    int rows;
    int cols;

public:
    // constructor Initialize all the values of matrix to zero
    Matrix();  // Set rows to MAXROWS and cols to MAXCOLS
    Matrix(int rows, int cols);
    //print Function
    void printMatrix();

    // Setter Functions
    void setMatrix(T[][3]);    //set the array to what is sent
    void addMatrix(T[][3]);   //add an array to matrix

    // No destructor needed
};

#endif //CLASSTEMPLATE_MATRIX_H

template<class T>
Matrix<T>::Matrix()
{
    rows = MAXROWS;
    cols = MAXCOLS;
}

template<class T>
Matrix<T>::Matrix(int rows, int cols)
{
    this->rows = rows;
    this->cols = cols;
}

template<class T>
void Matrix<T>::setMatrix(T array[][3])
{   
    //rows = sizeof(array)/sizeof(T);
    //cols = sizeof(array[0])/sizeof(T);
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
            matrix[i][j] = array[i][j];
    }
}

template<class T>
void Matrix<T>::printMatrix()
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
            std::cout << matrix[i][j] << "  ";

        std::cout << std::endl;
    }
}

template<class T>
void Matrix<T>::addMatrix(T otherArray[][3])
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
            matrix[i][j] += otherArray[i][j];
    }
}

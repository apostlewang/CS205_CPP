#include<iostream>
#include"complex.h"
using namespace std;
Complex::Complex(): real(0),imag(0){}
Complex::Complex(double re, double im): real(re),imag(im){}
Complex Complex::operator+(double real)const
{
    double result_real = real + this->real;
    return Complex(result_real,this->imag);
}
Complex Complex::operator+(const Complex& other)const
{
    double result_real = other.real + this->real;
    double result_imag = other.imag + this->imag;
    return Complex(result_real,result_imag);
}
Complex Complex::operator-(const Complex& other)const
{
    double result_real = this->real - other.real;
    double result_imag = this->imag - other.imag;
    return Complex(result_real,result_imag);
}
Complex Complex::operator*(const Complex& other)const
{
    double result_real = this->real*other.real-this->imag*other.imag;
    double result_imag = this->imag*other.real+other.imag*this->real;
    return Complex(result_real,result_imag);
}
bool Complex::operator==(const Complex& other)const
{
    return (this->real==other.real)&&(this->imag==other.imag);
}
bool Complex::operator!=(const Complex& other)const
{
    return !(this->real==other.real)&&(this->imag==other.imag);
}
Complex operator *(double real, const Complex& other){
    double result_real = real*other.real;
    double result_imag = real*other.imag;
    return Complex(result_real,result_imag);
}
Complex operator +(double real, const Complex& other){
    double result_real = real + other.real;
    return Complex(result_real,other.imag);
}
Complex operator ~(const Complex& other){
    double result_real = other.real;
    double result_imag = 0-other.imag;
    return Complex(result_real,result_imag);
}
std::ostream& operator<< (std::ostream& os, const Complex& other){
    os << other.real << " + " << other.imag << "i" << std::endl;
    return os;
}
void operator>> (std::istream& is, Complex& other){
    cout << "Enter a complex number" <<endl;
    double result_real;
    double result_imag;
    cout << "real: ";
    is >> result_real;
    cout << "imaginary: ";
    is >> result_imag;
    other.real = result_real;
    other.imag = result_imag;
    cout<<other<<endl;
}
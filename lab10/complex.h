class Complex{
private:
    double real;
    double imag;
public:
    Complex();
    Complex(double re, double im);
    Complex operator +(const Complex& other) const;
    Complex operator -(const Complex& other) const;
    Complex operator *(const Complex& other) const;
    bool operator ==(const Complex& other) const;
    bool operator !=(const Complex& other) const;
    Complex operator +(double real) const;
    friend Complex operator +(double real, const Complex& other);
    friend std::ostream& operator << (std::ostream& os, const Complex& other);
    friend void operator >> (std::istream& is, Complex& other);
    friend Complex operator ~(const Complex& other);
    friend Complex operator *(double real, const Complex& other);
};
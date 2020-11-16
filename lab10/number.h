class Number{
private:
    int value;
public:
    Number();
    Number(int value);
    Number operator ++(int a);
    Number operator --(int a);
    Number operator ++();
    Number operator --();
    friend std::ostream& operator <<(std::ostream& os, const Number& other);
};
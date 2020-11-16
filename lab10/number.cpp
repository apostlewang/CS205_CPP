#include<iostream>
#include"number.h"
using namespace std;
Number::Number(int value){
    this->value = value;
}
Number Number:: operator ++(){
    this->value+=1;
    return Number(this->value);
}
Number Number::operator --(){
    this->value-=1;
    return Number(this->value);
}
Number Number::operator ++(int){
    this->value+=1;
    return Number(this->value-1);
}
Number Number::operator --(int){
    this->value-=1;
    return Number(this->value+1);
}
ostream& operator <<(std::ostream& os, const Number& other){
    os << other.value << endl;
    return os;
}
int main(){
    Number n1(20);
    Number n2 = n1++;
    cout << n1 << endl;
    cout << n2 << endl;

    Number n3 = n2--;
    cout << n2 << endl;
    cout << n3 << endl;

    Number n4 = ++n3;
    cout << n3 << endl;
    cout << n4 << endl;

    Number n5 = --n4;
    cout << n4 << endl;
    cout << n5 << endl;
    return 0;
}
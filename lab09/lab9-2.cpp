#include<iostream>
using namespace std;

class Rectangle{
private:
    double width;
    double height;

public:
    Rectangle();
    Rectangle(double width,double height);
    double getArea(void);
    double getPerimeter(void);
    void display(void);
};

Rectangle::Rectangle(){
    width = 1;
    height = 1;
}
Rectangle::Rectangle(double width, double height){
    this->width = width;
    this->height = height;
}
double Rectangle::getArea(){
    return width*height;
}
double Rectangle::getPerimeter(){
    return 2*(width+height);
}
void Rectangle::display(){
    cout << "Width:" << width << endl;
    cout << "Height:" << height << endl;
    cout << "Area:" << getArea() << endl;
    cout << "Perimeter:" << getPerimeter() << endl;
}

int main(){
    Rectangle Rectangle1 = Rectangle(4,40);
    Rectangle Rectangle2 = Rectangle(3.5,35.9);
    Rectangle1.display();
    Rectangle2.display();
    return 0;
}
/*
 * @Date: 2020-11-30 10:33:15
 * @Author: Kang Wang
 * @LastEditors: Kang Wang
 * @LastEditTime: 2020-11-30 20:10:23
 */
#include<iostream>
#include <iomanip>
#include<math.h>
using namespace std;
class CStereoShape{
private:
   static int numberOfObject;
public:
    CStereoShape(){       
        numberOfObject++;
    }
    virtual float GetArea(){
        cout << "CStereoShape::GetArea" << endl;
        return 0.0;
    }
    virtual float GetVolume(){
        cout << "CStereoShape::GetVolume" << endl;
        return 0.0;
    }
    virtual void Show(){
        cout << "CStereoShape::Show" << endl;
    }
    int GetNumOfObject(){
        return numberOfObject;
    }
};

int CStereoShape::numberOfObject = 0;
class CCube : public CStereoShape{
private:
    float length;
    float width;
    float height;  
public:
    CCube():CStereoShape(){
        length = 2.0;
        width = 2.0;
        height = 2.0;
    }
    CCube(float length, float width, float height):CStereoShape(){
        this->length = length;
        this->width = width;
        this->height = height;
    }
    CCube(CCube &c):CStereoShape(){
        length = c.length;
        width = c.width;
        height = c.height;
    }
    float GetArea(){
        return 2*(length*width+length*height+width*height);
    }
    float GetVolume(){
        return length*width*height;
    }
    void Show(){
        cout << "length: " << length << endl;
        cout << "width: " << width << endl;
        cout << "height: " << height << endl;
        cout << "surface area: " << GetArea() << endl;
        cout << "volume: " << GetVolume() << endl;
    }
};

class CSphere : public CStereoShape{
private:
    float radius;
public:
    CSphere():CStereoShape(){
        radius = 5.0;
    }
    CSphere(float radius):CStereoShape(){
        this->radius = radius;
    }
    CSphere(CSphere &c):CStereoShape(){
        radius = c.radius;
    }
    float GetArea(){
        return 4*M_PI*pow(radius,2);
    }
    float GetVolume(){
        return 4*M_PI*pow(radius,3)/3;
    }
    void Show(){
        cout << "radius: " << radius << endl;
        cout << "surface area: " << GetArea() << endl;
        cout << "volume: " << GetVolume() << endl;
    }
};

int main(){
    CCube a_cube(4.0,5.0,6.0);
    CSphere c_sphere(7.9);
    CStereoShape* p = &a_cube;
    p->Show();
    cout << endl;
    p = &c_sphere;
    p->Show();
    cout << p->GetNumOfObject();
    return 0;
}


/*
 * @Date: 2020-12-14 19:42:36
 * @Author: Kang Wang
 * @LastEditors: Kang Wang
 * @LastEditTime: 2020-12-14 20:43:32
 */
#include<iostream>
using namespace std;
class OutOfRangeException: public exception
{
public:
    int idx;
    int number;
    OutOfRangeException(int idx, int number){
        this -> idx = idx;
        this -> number = number;
    }
};
float calculateAverage(int a, int b, int c, int d){
    float average;
    if(a > 100 || a < 0){
        throw OutOfRangeException(1, a);
    }
    if(b > 100 || b < 0){
        throw OutOfRangeException(2, b);
    }
    if(c > 100 || c < 0){
        throw OutOfRangeException(3, c);
    }
    if(d > 100 || d < 0){
        throw OutOfRangeException(4, d);
    }
    average = (a + b + c + d)/4;
    return average;  
}
int main(){
    while(true){
        cout << "Please enter marks for 4 courses:" << endl;
        int a, b, c, d;
        cin >> a;
        cin >> b; 
        cin >> c;
        cin >> d;
        float ave;
        try{
            ave = calculateAverage(a,b,c,d);
        }
        catch(OutOfRangeException &e){
            cerr << "The parameter " << e.idx << " is " << e.number \
            << ", which is out of range (0-100)" << endl; 
            continue;
        }
        cout << "The average of the four courses is " << ave << endl;
        cout << "Another 4 courses(y/n)?";
        char flag;
        cin >> flag;
        if(flag == 'y'){
            continue;
        }
        else{
            cout << "Bye" << endl;
            break;
        }
    }
    return 0;
}
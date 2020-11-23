#include<iostream>
using namespace std;
int main(){
    cout << "Enter 3 scores" << endl;
    double a,b,c;
    cin >> a;
    cin >> b;
    cin >> c;
    double sum,ave;
    sum = a+b+c;
    ave = sum/3.0;
    cout << "average score = " << ave << endl;
    if(ave>=90){
        cout << "grade = A";
    }
    else if(ave>=70){
        cout << "grade = B";
    }
    else if(ave>=50){
        cout << "grade = C";
    }else {
        cout << "grade = F";
    }
    return 0;
}
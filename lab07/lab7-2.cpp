#include<iostream>
using namespace std;

template <typename T>
T Max5(T x[]){
    T max = x[0];
    for(int i = 1 ;i < 5; i++){
        if(x[i]>max){
            max = x[i];
        }
    }
    return max;
}
int main(){
    double a[] = {1.1,2.0,3.0,4.0,5.5};
    int b[] = {1,2,3,4,5};
    cout << "MaxInt =" << Max5(b)<< endl;
    cout << "MaxDouble =" << Max5(a)<< endl;
    return 0;
}
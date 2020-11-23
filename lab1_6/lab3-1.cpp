#include<iostream>
using namespace std;
int main(){
    int sum = 0;
    while(1){
        int a = 0;
        cout << "Enter an integer number:" <<endl;
        cin >> a;
        sum += a;
        cout << "The cumulative sum is: " << sum <<endl;
        if(a==0){
            break;
        }
    }
    return 0;
}
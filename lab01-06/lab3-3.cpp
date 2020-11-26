#include<iostream>
using namespace std;
int main(){
    for (int i = 0; i < 7; i++)
    {
        for (int j = 0; j < i+1; j++){
            cout << j+1;
        }
        for (int j = 0; j < 6-i; j++){
            cout << "*";
        }

        cout<<endl;
    }
    
    return 0;
}
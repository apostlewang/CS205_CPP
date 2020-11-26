#include<iostream>
using namespace std;
int main(){
    int *array = NULL;
    array = new int [5];
    cout << "Enter 5 integers" << endl;
    for(int i = 0; i < 5; i++){
        cin >> array[i];
    }
    array += 5;
    for(int i = 0; i < 5; i++){
        array--;
        cout << *array << " ";       
    }
    delete array;
    return 0;
}
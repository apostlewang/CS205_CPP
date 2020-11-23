#include<iostream>
using namespace std;
void print(){
    cout << "Smile! ";
}
int main(){
    for (int i = 0; i < 3; i++)
    {
        print();
    }
    cout << endl;

    for (int i = 0; i < 2; i++)
    {
        print();
    }
    cout << endl;

    print();
    return 0;
}
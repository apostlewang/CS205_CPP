#include <iostream>
#include "stack.h"
using namespace std;
int main()
{
    Stack a = Stack(1);
    Stack b = Stack(20);
    for(int i = 0;i < 5; i++){
        b.push(i);
    }
    Stack c = b;
    Item poped;
    cout << "b5 poped:" << endl;
    while(b.pop(poped)){
        cout << poped << endl;
    }
    a.push(0);
    b = a;
    cout << "b=a1 poped:" << endl;
    while(b.pop(poped)){
        cout << poped << endl;
    }
    Stack d = Stack(c);
    cout << "d=c5 poped:" << endl;
    while(d.pop(poped)){
        cout << poped << endl;
    }
    return 0;
}
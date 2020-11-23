#include <iostream>
#include"stack.h"
using namespace std;
Stack::Stack(int n)
{
    size = n;
    top = 0;
    pitems = new Item[n];

}
Stack::Stack(const Stack & st)
{
    size = st.size;
    top = st.top;
    pitems = new Item[size];
    for(int i = 0;i < top; i++){
        pitems[i] = st.pitems[i];
    }
}
Stack::~Stack()
{
    delete [] pitems;
}
bool Stack::isempty() const{
    return top == 0;
};
bool Stack::isfull() const{
    return size == top;
};
bool Stack::push(const Item & item){
    if(isfull()){
        return false;
    }
    pitems[top] = item;
    top++;
    return true;
};
bool Stack::pop(Item & item){
    if(isempty()){
        return false;
    }
    top--;
    item = pitems[top];
    return true;
};
Stack& Stack::operator= (const Stack &st){
    if (this == &st){
        return *this;
    }
    delete [] pitems;
    size = st.size;
    top = st.top;
    pitems = new Item[st.size];
    for(int i = 0;i < top; i++){
       pitems[i] = st.pitems[i];
    }
    return *this;
};
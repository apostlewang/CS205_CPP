#include<iostream>
#include<string>
using namespace std;
struct CandyBar{
    string name;
    float weight;
    int calories;

};

int main(){
    CandyBar myCandy;
    cout<<"Enter brand name:"<<endl;
    getline(cin,myCandy.name);
    cout<<"Enter weight:"<<endl;
    cin>>myCandy.weight;
    cout<<"Enter calories:"<<endl;
    cin>>myCandy.calories;
    cout<<"Brand: "<<myCandy.name<<endl;
    cout<<"Weight: "<<myCandy.weight<<endl;
    cout<<"Calories: "<<myCandy.calories<<endl;
    return 0;
}
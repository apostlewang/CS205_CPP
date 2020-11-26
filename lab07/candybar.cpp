#include<iostream>
using namespace std;
struct CandyBar{
    string brand;
    float weight;
    int calories;
};
void set(CandyBar &cb){
    cout<<"Enter brand name:"<<endl;
    getline(cin,cb.brand);
    cout << "Enter weight:"<<endl;
    cin >> cb.weight;
    cout << "Enter calories:"<<endl;
    cin >> cb.calories;

}
void set(CandyBar* const cb){
    cout<<"Enter brand name:"<<endl;
    getline(cin,cb->brand);
    cout << "Enter weight:"<<endl;
    cin >> cb->weight;
    cout << "Enter calories:"<<endl;
    cin >> cb->calories;

}
void show(const CandyBar & cb){
    cout << "Brand name: " << cb.brand << endl;
    cout << "Weight: " << cb.weight << endl;
    cout << "Calories: " << cb.calories << endl;
}
void show(const CandyBar* cb){
    cout << "Brand name: " << cb->brand << endl;
    cout << "Weight: " << cb->weight << endl;
    cout << "Calories: " << cb->calories << endl;
}

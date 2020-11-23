#include<iostream>
#include<string>
using namespace std;
struct CandyBar{
    string name;
    float weight;
    int calories;

};
int main(){
    CandyBar *myCandy;
    myCandy = new (nothrow) CandyBar[3];
    for(int i = 0; i < 3; i++){
        cout<<"Enter brand name:"<<endl;
        getchar();
        getline(cin,myCandy[i].name);
        cout<<"Enter weight:"<<endl;
        cin>>myCandy[i].weight;
        cout<<"Enter calories:"<<endl;
        cin>>myCandy[i].calories;
    }
    cout<<endl<<"Displaying the CandyBar array contents"<<endl;
    for(int i = 0; i < 3; i++){
        cout << "Brand name: " << myCandy[i].name << endl;
        cout << "Weight: " << myCandy[i].weight << endl;
        cout << "Calories: " << myCandy[i].calories << endl;
    }
    return 0;
}
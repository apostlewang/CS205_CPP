#include<iostream>
#include<string>
using namespace std;
struct CandyBar{
    string name;
    float weight;
    int calories;
    float ratio;
};
int main(){
    CandyBar myCandy [3];
    for(int i = 0; i < 3; i++){
        cout<<"Enter brand name:"<<endl;
        getchar();
        getline(cin,myCandy[i].name);
        cout<<"Enter weight:"<<endl;
        cin>>myCandy[i].weight;
        cout<<"Enter calories:"<<endl;
        cin>>myCandy[i].calories;
        myCandy[i].ratio=myCandy[i].calories/myCandy[i].weight;
    }

    cout<<endl<<"Displaying the CandyBar array contents"<<endl;
    int index = 0;
    if(myCandy[0].ratio < myCandy[1].ratio){
        if(myCandy[1].ratio < myCandy[2].ratio){
            index = 2;
        }
        else{
            index = 1;
        }
    }
    else{
        if(myCandy[0].ratio < myCandy[2].ratio){
            index = 2;
        }
        else{
            index = 0;
        }
    }
    for(int i = 0; i < 3; i++){
        cout<<"Brand: "<<myCandy[i].name<<endl;
        cout<<"Weight: "<<myCandy[i].weight<<endl;
        cout<<"Calories: "<<myCandy[i].calories<<endl;
        
    }
    cout << "The greatest calories per weight is" <<endl;
    cout << "Brand name:"<< myCandy[index].name <<endl;
    cout << "Calories per weight:"<< myCandy[index].ratio <<endl;
    return 0;
}
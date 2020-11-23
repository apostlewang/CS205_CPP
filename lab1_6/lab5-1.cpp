#include<iostream>
using namespace std;

struct pizza{
    string company;
    int diameter;
    float weight;
};

int main( ){
    pizza *myPizza = NULL;
    myPizza =new pizza;

    cout << "Enter the company:" << endl;
    getline(cin,myPizza->company);

    cout << "Enter the diameter:" << endl;
    cin >> myPizza->diameter;
    
    cout << "Enter the weight:" << endl;
    cin >> myPizza->weight;
    

    cout << "Display the info:" << endl;
    cout << "Company name: " << myPizza->company << endl;
    cout << "Pizza diameter: "<< myPizza->diameter << endl;
    cout << "Pizza weight: "<< myPizza->weight << endl;

    delete myPizza;
    return 0;
}

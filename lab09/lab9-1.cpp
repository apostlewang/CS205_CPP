#include<iostream>
using namespace std;

class CandyBar{
private:
    string brand;
    float weight;
    int calories;
public:
    CandyBar();
    void setCandyBar(void);
    void showCandyBar(void);
};

CandyBar::CandyBar(){
    brand = "";
    weight = 0;
    calories = 0;
}

void CandyBar::setCandyBar(){
    cout<<"Enter brand name:"<<endl;
    getline(cin,brand);
    cout << "Enter weight:"<<endl;
    cin >> weight;
    cout << "Enter calories:"<<endl;
    cin >> calories;

}

void CandyBar::showCandyBar(){
    cout << "Brand name: " << brand << endl;
    cout << "Weight: " << weight << endl;
    cout << "Calories: " << calories << endl;
}

int main(){
    CandyBar c = CandyBar();
    c.setCandyBar();
    c.showCandyBar();

}
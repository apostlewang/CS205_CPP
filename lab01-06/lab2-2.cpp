#include<iostream>
using namespace std;
int main(){
    cout<<"Enter the number of seconds:"<<endl;
    long long seconds;
    cin >> seconds;
    int s = seconds%60;
    long long minutes = seconds/60;
    int m = minutes%60;
    long long hours = minutes/60;
    int h = hours%24;
    long long days = hours/24;
    cout << seconds <<" seconds = " << days << " days, " << h << "hours, " << m << "minutes, " << s <<" seconds";


}
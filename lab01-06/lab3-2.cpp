#include<iostream>
#include<cstring>
using namespace std;
int main(){
    int sum = 0;
    string word;
    cout << "Enter words(to stop, type \"done\"):" << endl;
    while(1){
        cin >> word;
        if(word=="done"){
            break;
        }
        sum++;
    }
    cout << "You entered a total of " << sum <<" words"<< endl;

    return 0;
}
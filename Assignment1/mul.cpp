#include <iostream>
using namespace std;

int main(){
    long long a;
    long long b;
    long long result;
    cout << "Please input the first multiplier:" << endl;
    cin >> a;
    while(cin.fail()){
      cin.clear();
      cout << "Wrong data type, Please input an integer!" << endl; 
      cin.ignore(9999,'\n');
      cin >> a;
    }

    cout << "Please input the second multiplier:" << endl;
    cin >> b;
    while(cin.fail()){
      cin.clear();
      cout << "Wrong data type, Please input an integer!" << endl; 
      cin.ignore(9999,'\n');
      cin >> b;
    }

    result = a*b;

    if(result/a == b){
        cout << "The result is:\n" << result;
    }
    else{
        cout << "Two multipliers are too large, result overflows" << endl;
    }
    
    return 0;
}



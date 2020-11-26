#include<fstream>
#include<iostream>
#include<string>
using namespace std;
int main(){
    char input[80];
    string output;
    
    
    ofstream outfile1("f1.txt", ios::trunc);
    ofstream outfile2("f2.txt", ios::trunc);
    fstream f1("f1.txt");
    fstream f2("f2.txt");
    if(f1.good()){
        cout << "Please input a string:" << endl;
        cin.getline(input,80);
        f1 << input << endl;
        f1.clear();
        f1.seekg(0);
    }
    cout << "The contents of f1.txt:";
    while(getline(f1,output)){     
        cout << output << endl;
    }
    f1.close();
    char out[80];
    for(int i = 0;i < 80;i++){
        char ch = input[i];
        if(ch>='a'&& ch<='z'){
            out[i]=input[i]-32;
        }
        else{
            out[i]=input[i];
        }
    }
    
     
    if(f2.good()){
        f2 << out << endl;
        f2.clear();
        f2.seekg(0);
    }
    cout << "The contents of f2.txt:";
    while(getline(f2,output)){     
        cout << output << endl;
    }
    f2.close();
    return 0;
}
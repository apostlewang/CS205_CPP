#include <iostream>
#include <time.h>
#include <stdint.h>
#include <x86intrin.h>
#include <xmmintrin.h>
#include "cblas.h"
using namespace std;

float dotProduct(float *v1, float *v2, int length);

void userInput(){
    
    int myLength;
    cout << "Please input the length of 2 vectors"<< endl;
    cin >> myLength;
    while(cin.fail()|| myLength <= 0){
      cin.clear();
      cout << "Wrong data type, please input an postive integer!" << endl; 
      cin.ignore(9999,'\n');
      cin >> myLength;
    }
    float *v1 = new float[myLength];
    float *v2 = new float[myLength];
    int count = 0;
    float temp;
    string tes;
    cout << "Please input the components of the first vector:" << endl;
    while(1){
        cin >> temp;
        while(cin.fail()){
            cin.clear();
            cout << "Wrong data type, please input a float number!" << endl; 
            cin.ignore(9999,'\n');
            cin >> temp;
        }
        v1[count] = temp;  
        count ++;
        if(count == myLength){
            break;
        }   
    }
    
    cout << "Please input the components of the second vector:" << endl;
    count = 0;  
    while(1){
        cin >> temp;
        while(cin.fail()){
            cin.clear();
            cout << "Wrong data type, please input a float number!" << endl; 
            cin.ignore(9999,'\n');
            cin >> temp;
        }
        v2[count] = temp;  
        count ++;
        if(count == myLength){
            break;
        }   
    }

    float userResult = dotProduct(v1,v2,myLength);
    cout << "The result is: " << userResult << endl;
}

float dotProduct(float *v1, float *v2, int length){
    
    double result = 0;
//  #pragma omp parallel for num_threads(4) reduction(+:result)
    
    for(int i = 0; i < length; i++){
        result += v1[i] * v2[i]; 
    }
    return (float)result;
}
//refer https://zhou-yuxin.github.io/
//https://blog.csdn.net/fuwenyan/article/details/77742766
float fastProduct(float *v1, float *v2, int length){
    double result = 0;
    int i = 0;
    int end = length&(~3);
  //#pragma omp parallel for num_threads(8) 
  //#pragma omp parallel for reduction(+:result)
    for(i=0 ; i<end; i+=4){//128=4*32
        __m128 A=_mm_load_ps(v1+i);
        __m128 B=_mm_load_ps(v2+i);
        __m128 C=_mm_dp_ps(A,B,0xf1);
        result += C[0];
    }
    for(;i<length;i++)
        result+=v1[i]*v2[i];
    return (float)result;
}

float * generator(int size){
    float * v1 = new float[size];
    for(int i = 0; i < size; i++){
       v1[i] = rand()/10.0f; 
    }
    return v1;
}

void testSpeed(int length){
    float* v1 = generator(length);
    float* v2 = generator(length);
    
    clock_t start,end;
    start = clock();
    float result = dotProduct(v1, v2, length);
    end = clock();
    cout<<"Original version:"<<endl;
    cout<<"The result is: "<<result<<endl;
    cout<<"The time for "<< length <<" data is "<<double(end-start)/CLOCKS_PER_SEC<<"s"<<endl;
    cout<<endl;

    start = clock();
    result = fastProduct(v1, v2, length);
    end = clock();
    cout<<"Faster version:"<<endl;
    cout<<"The result is: "<<result<<endl;
    cout<<"The time for "<< length <<" data is "<<double(end-start)/CLOCKS_PER_SEC<<"s"<<endl;
    cout<<endl;

    start = clock();
    result = cblas_sdot(length,v1,1,v2,1);
    end = clock();
    cout<<"OpenBlas version:"<<endl;
    cout<<"The result is: "<<result<<endl;
    cout<<"The time for "<< length <<" data is "<<double(end-start)/CLOCKS_PER_SEC<<"s"<<endl;
    cout<<endl;
}

int main(){
    int length = 30e7;
    testSpeed(length);
    userInput();
    return 0;
}


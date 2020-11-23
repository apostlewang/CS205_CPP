#include<iostream>
using namespace std;

int Fill_array(double arr[], int size){
    int i = 1;
    int value = 0;
    while(i <= size){
        cout << "Enter value #" << i << endl;
        cin >> value;
        if(cin.fail()){
            break;
            return i-1;
        }
        arr[i-1] = value;
        i++;
    }
    return size;
 
}

void Show_array(double *arr, int size){
    for(int i = 0; i < size; i++){
        cout << arr[i] << " ";
    }
    cout << endl;
}

void Reverse_array(double *arr, int size){
    int left = 0;
    int right = size -1;
    while(left < right){
        int temp = arr[left];
        arr[left] = arr[right];
        arr[right] = temp;
        left ++;
        right --;
    }
}
int main(){
    int size;
    cout << "Enter the size of an array:" << endl;
    cin >> size;
    double *array = new double[size];
    Fill_array(array,size);
    Show_array(array,size);
    Reverse_array(array,size);
    Show_array(array,size);
    Reverse_array(array+1,size-2);
    Show_array(array,size);
    return 0;
}
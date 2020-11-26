#include<iostream>
using namespace std;
struct box{
    char maker[40];
    float height;
    float width;
    float length;
    float volume;
};

void display(box myBox){
    cout << "Maker: " << myBox.maker << endl;
    cout << "Height: " << myBox.height << endl;
    cout << "Width: " << myBox.width << endl;
    cout << "Length: " << myBox.length << endl;
    cout << "Volume: " << myBox.volume << endl;
}

void setVolume(box &myBox){
    myBox.volume = myBox.height * myBox.length * myBox.width;
}

int main(){
    box myBox;
    char maker[40] = "Jack Smith";
    strcpy(myBox.maker,maker);
    myBox.height = 3.4;
    myBox.width = 4.5;
    myBox.length = 5.6;
    myBox.volume = 0;
    cout << "Before setting volume:" << endl;
    display(myBox);
    cout << "After setting volume:" << endl;
    setVolume(myBox);
    display(myBox);
    return 0;
}
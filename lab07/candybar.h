#ifndef EXE_CANDYBAR_H
#define EXE_CANDYBAR_H
#include<iostream>
#endif
using namespace std;
struct CandyBar{
    string brand;
    float weight;
    int calories;
};

void set(CandyBar* const cb);
void set(CandyBar &cb);
void show(const CandyBar & cb);
void show(const CandyBar* cb);
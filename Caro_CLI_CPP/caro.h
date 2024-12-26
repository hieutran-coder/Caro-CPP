#ifndef CARO_H
#define CARO_H
#include<iostream>
#include"display.h"
#include"match.h"
#include"thread"
using namespace std;

class Caro
{
private:
    //int mask[10][10];
public:
    Caro();
    int winCheck(int mask[][10]);  // check state of match
    void replay(vector<Cell> &replay); // replay lại match
};

#endif // CARO_H

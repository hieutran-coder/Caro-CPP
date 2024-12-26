#ifndef DISPLAY_H
#define DISPLAY_H

#include<iostream>
using namespace std;
#define M 10
class Display
{
public:
    Display();
    void displayMenu();
    void displayBotOption();
    void displayPlayerInfoOption();
    void displayCaroTableWithMask(int display[][4*M + 1]);
};

#endif // DISPLAY_H

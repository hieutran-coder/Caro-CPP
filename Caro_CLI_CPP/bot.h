#ifndef BOT_H
#define BOT_H
#include"match.h"
#include<iostream>

// Mở rộng thành 3 bot kế thừa 1 bot
class Bot
{
private:
    string level;
public:
    Bot();
    Bot(string level): level(level){};

    string getLevel() const;
    void setLevel(const string &newLevel);
    Cell readGame(vector<Cell> &replay);
};

#endif // BOT_H

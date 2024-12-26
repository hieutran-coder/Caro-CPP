#ifndef MATCH_H
#define MATCH_H
#include"player.h"
#include<vector>
#include"filehandlingexception.h"
struct Cell{
    int x,y;
    Cell(){};
    Cell(int x, int y): x(x), y(y){}
};

class Match
{
private:

    int state = -1; // chưa xác định
    Player* p1, *p2;
    vector<Cell> Replay;
    // string time;
    // string matchType;
public:
    Match();

    void setReplay(const vector<Cell> &newReplay);
    vector<Cell>& getReplay() ;
    void newMatch(Player *p1, Player *p2);
    int getState() const;
    void setState(int newState);
    void showWinner();

    void save(std::string address); // Chỉ lưu match cuối của 2 người chơi. Ko lưu với bot
};
/*
Lưu file:
    1. Player 1:
    2. Player 2:
    3. Replay
    4. State
    5. Time

*/


#endif // MATCH_H

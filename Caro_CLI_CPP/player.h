#ifndef PLAYER_H
#define PLAYER_H
#include<iostream>
#include<iomanip>
using namespace std;


class Player
{
private:
    std::string name;
    int numberOfWins, numberOfDraws, numberOfLooses;
public:
    Player();
    Player(string name, int numberOfWins, int numberOfDraws, int numberOfLooses);
    void displayPlayerInfo();
    void input();
    std::string getName() const;
    int getNumberOfWins() const;
    int getNumberOfDraws() const;
    int getNumberOfLooses() const;
    int getTotalPoints();
    void displayPlayerInfoWithPoints(); // 3 - win, 1 - draw, 0 - loose
    int getRank();
    void displayPlayerInfoWithRanks();
    void setNumberOfWins(int newNumberOfWins);
    void setNumberOfDraws(int newNumberOfDraws);
    void setNumberOfLooses(int newNumberOfLooses);
    void setName(const std::string &newName);
    void inputNewPlayer();

};

void displayTitle();


#endif // PLAYER_H

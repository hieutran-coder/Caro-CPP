#ifndef PLAYERMANAGER_H
#define PLAYERMANAGER_H
#include<iostream>
using namespace std;
#include"player.h"
#include<vector>

class PlayerManager
{
public:
    PlayerManager();
    vector<Player> &rankingPlayers(vector<Player> &players);
    vector<Player> searchPlayer(string name, vector<Player> &players);
    vector<int> searchPlayerIndex(string name, vector<Player> &players);
    void findEquivalentPlayers(Player p, vector<Player> &players);
};


#endif // PLAYERMANAGER_H

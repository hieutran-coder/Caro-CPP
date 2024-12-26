#ifndef FILEMANAGER_H
#define FILEMANAGER_H
#include"player.h"
#include<fstream>
#include<iostream>
#include"filehandlingexception.h"
#include"match.h"



class FileManager
{
public:
    FileManager();
    vector<Player>  loadPlayersInfo(string address);
    vector<Player> readFile(const std::string &filename); // ko dùng
    Match loadMatch(string address);

    void readGuild(string filename);

    void savePlayersInfoToFile(string address, vector<Player> &players);


};


#endif // FILEMANAGER_H

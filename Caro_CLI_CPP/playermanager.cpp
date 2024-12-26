#include "playermanager.h"

PlayerManager::PlayerManager() {}



vector<Player>& PlayerManager::rankingPlayers( vector<Player>& players){

    std::sort(players.begin(),players.end(), [] (Player player1,Player player2){
        return player1.getTotalPoints()> player2.getTotalPoints();
    } );
    return players;
}

vector<Player>  PlayerManager::searchPlayer(string name, vector<Player>& players ){
    vector<Player> foundPlayers;

    for(auto player:players){
        if(player.getName() == name){
            player.displayPlayerInfo();
            foundPlayers.push_back(player);
        }
    }

    while(foundPlayers.size() == 0){
        cin.clear();
        cin.ignore(); // True
        //cin.ignore(std::numeric_limits<streamsize>::max()); --> why wrong
        cout<<"Can not find anyone. Yêu cầu nhập lại tên";
        getline(cin, name);

        for(auto player:players){
            if(player.getName() == name){
                player.displayPlayerInfo();
                foundPlayers.push_back(player);
            }
        }
    }

    return foundPlayers;
}

// update from chatgpt
vector<int> PlayerManager::searchPlayerIndex(string name, vector<Player>& players) {
    vector<int> allIndexHasSameName;

    // Search for players with the given name
    for (size_t i = 0; i < players.size(); ++i) {
        if (players[i].getName() == name) {
            players[i].displayPlayerInfo();
            allIndexHasSameName.push_back(i);
        }
    }

    // If no players found, prompt user to re-enter the name
    while (allIndexHasSameName.empty()) {
        cin.clear();
        cin.ignore(); // Clear the input buffer
        cout << "Cannot find anyone. Please enter the name again: ";
        getline(cin, name);

        // Search again with the new name
        for (size_t i = 0; i < players.size(); ++i) {
            if (players[i].getName() == name) {
                players[i].displayPlayerInfo();
                allIndexHasSameName.push_back(i);
            }
        }
    }

    return allIndexHasSameName;
}




void PlayerManager::findEquivalentPlayers(Player p, vector<Player>& players){

    for(auto& player: players){
        if(p.getRank() == player.getRank()) player.displayPlayerInfoWithRanks();
    }

}

#include "filemanager.h"
#include<vector>
FileManager::FileManager() {}


vector<Player>  FileManager::loadPlayersInfo(string address){

    ifstream file(address);

    if(!file){
        throw FileHandlingException("Can not open file to read");
    }

    vector<Player> players;

    string name; int w, l, d;
    char delimiter;

    // P/án 1: dùng thằng file
    while(std::getline(file,name,',')){ ;
        // con trỏ luồng đang đến vị trí nào?--> Sau comma còn dấu cách --> Lỗi--> Solution: file.ignore()
        file.ignore(); // bỏ qua dấu cách
        file>>w>>delimiter;
        file.ignore();
        file>>l>>delimiter;
        file.ignore();
        file>>d;
        file.ignore(); //bỏ qua kí tự xuống dòng

        //cout<<name<<" "<<w<<" "<<l<<" "<<d;
        players.push_back(Player(name, w, l,d));
    }

    file.close();
    return players;
}


void FileManager::savePlayersInfoToFile(string address, vector<Player>& players){

    ofstream file(address);

    if (!file){
        throw::FileHandlingException("Can not open file");
        // cerr<<"Can not open file"<<endl;
    }

    // đẩy data vào file
    for(auto &player: players){
        file<<player.getName()<<", "<<player.getNumberOfWins()<<", "<<player.getNumberOfLooses()<<", "<<player.getNumberOfDraws()<<"\n";
        file.flush(); // xả trực tiếp dữ liệu vào file từ buffer associated với file object, không đợi đến khi file.close() mới xả
    }

    file.close();
    //cout<<"successfully save to file";
}

// Đọc từ file match
Match FileManager::loadMatch(string address){
    ifstream file(address);

    if(!file){
        throw FileHandlingException("Can not open file to read");
    }

    std::string line;
    Match m;
    std::getline(file, line); // Đọc dòng player 1 --> chưa xong
    std::getline(file, line); // Dọc dòng player 2
    std::getline(file, line); // Đọc trạng thái
    m.setState(line[0]-'0');

    std::vector<Cell> replay;
    // This code Using code from ChatGPT
    while (std::getline(file, line)) {
        size_t pos = 0;
        while (pos < line.size()) {
            if (line[pos] == '(') {
                size_t comma = line.find(',', pos);
                size_t end = line.find(')', pos);
                if (comma != std::string::npos && end != std::string::npos) {
                    int x = std::stoi(line.substr(pos + 1, comma - pos - 1));
                    int y = std::stoi(line.substr(comma + 1, end - comma - 1));
                    replay.push_back({x, y});
                    pos = end + 1;
                } else {
                    break; // Error in format
                }
            } else {
                ++pos;
            }
        }
    }
    m.getReplay() = replay;
    return m;

}


// Đọc từ guild
void FileManager::readGuild(string filename){
    std::ifstream file(filename);

    if(!file.is_open()){
        throw FileHandlingException("Can not open file:" + filename);
    }

    vector<Player> players;
    std::string line;
    std::string name; int w, l, d;
    char delimiter;

    while(std::getline(file, line)){
        if (file.fail()){  // Fail ==> Lỗi xảy ra trong khi đọc ghi
            throw FileHandlingException("Error when read file" + filename);
        }
        cout<<line<<endl;
    }

    // Bad => Lỗi phần cứng, không thể đọc ghi tiếp
    if (file.bad()){
        throw FileHandlingException("Important error when read file" + filename);
    }

}

// Three keyword of ifstream: is_open, fail, bad.
vector<Player> FileManager::readFile(const std::string& filename){
    std::ifstream file(filename);

    if(!file.is_open()){
        throw FileHandlingException("Can not open file:" + filename);
    }

    vector<Player> players;
    std::string line;
    std::string name; int w, l, d;
    char delimiter;

    while(std::getline(file, line,',')){
        if (file.fail()){  // Fail ==> Lỗi xảy ra trong khi đọc ghi
            throw FileHandlingException("Error when read file" + filename);
        }
        //std::cout<<line<<std::endl;
        // con trỏ luồng đang đến vị trí nào?--> Sau comma còn dấu cách --> Lỗi--> Solution: file.ignore()
        file.ignore(); // bỏ qua dấu cách
        file>>w>>delimiter;
        file.ignore();
        file>>l>>delimiter;
        file.ignore();
        file>>d;
        file.ignore(); //bỏ qua kí tự xuống dòng

        //cout<<name<<" "<<w<<" "<<l<<" "<<d;
        players.push_back(Player(name, w, l,d));
    }

    // Bad => Lỗi phần cứng, không thể đọc ghi tiếp
    if (file.bad()){
        throw FileHandlingException("Important error when read file" + filename);
    }

    return players;
}



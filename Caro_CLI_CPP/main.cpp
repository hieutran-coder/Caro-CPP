#include <iostream>
#include<vector>
using namespace std;
#include<thread>
#include<limits>
#include"player.h"
#include"match.h"
#include<fstream>
#include"filehandlingexception.h"
#include<thread>
#include"bot.h"
#include"filemanager.h"
#include"display.h"
#include"playermanager.h"
#include"caro.h"


const int WIN_LENGTH = 4;
const int N = 10;
int mask[N][N];


int display[2*N+1][4*N + 1]; // 0: Khoảng trắng, 1: 0, 2: X



// Valid input
int validOpt(int opt, int left, int right){
    while( !(cin>>opt)||opt<left||opt>right)
    {
        //cout<<opt;
        cout<<"Nhập vào không hợp lệ!!";
        cout<<"Yêu cầu nhập lại: ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    return opt;
}




// Still not done: 1. Save match
void continuePlayPreviousMatch(FileManager fm, Display d, Caro cr){
    Match m = fm.loadMatch("match.txt");
    int mask1[10][10];

    for(int i = 0; i<10; i++)
        for(int j = 0; j<10; j++)
            mask1[i][j] = 0;


    if(m.getState() == -1){
        cout<<"Your previous match doesn't end. Do you want to continue this match?. Press 0 or 1 for yes or no: ";
        int popt;
        popt = validOpt(popt,0,1);
        if (popt == 0) return;
        else{
            vector<Cell> replay = m.getReplay();
            for(int i = 0; i<2*N + 1; i++)
                for(int j = 0; j<4*N + 1; j++)
                    display[i][j] = 0;

            for(int i = 0; i<replay.size(); i++){
                if(i%2){
                    mask1[ replay[i].x ][ replay[i].y ] =1;
                    display[2*replay[i].x + 1 ][4*replay[i].y +2] = 2;
                }
                else{
                    mask1[replay[i].x][replay[i].y] =2;
                    display[2*replay[i].x + 1 ][4*replay[i].y +2] = 1;
                }

            }

            d.displayCaroTableWithMask(display);
            int turn;
            if(m.getReplay().size()%2) turn = 2;
            else turn = 1;
            Cell c;
            do{
                cout<<"\nPlayer "<<turn<<" move: ";
                cin>>c.x>>c.y;
                while(mask1[c.x][c.y]!=0||c.x>=N||c.y>=N||c.x<=-1||c.y<=-1){
                    cout<<"Ô này không đánh được.Yêu cầu nhập lại: ";
                    cin>>c.x>>c.y;
                }

                //Cập nhật 3 cấu trúc dữ liệu
                display[2*c.x + 1 ][4*c.y+2] = turn; // display là để hiển thị trạng thái
                mask1[c.x][c.y] = turn;  //trạng thái đánh hiện tại
                m.getReplay().push_back(c);

                std::cout<< u8"\033[2J\033[1;1H";
                // Hiển thị sau khi đánh
                d.displayCaroTableWithMask(display);

                // m.save("match.txt");

                if(cr.winCheck(mask1)!=0){
                    int temp = cr.winCheck(mask1);

                    //m.save("match.txt"); // lỗi ở việc chỉ số thắng thua
                    // report result
                    break;

                }
                turn = 3 - turn;
                if(m.getReplay().size() == N*N) { // can optimize
                    m.setState(0);
                    cout<<"two player draw";

                    // Số trận hòa của 2 người chơi tăng
                    //m.save("match.txt");
                    break;
                }
            }while(1);



        }
    }
    return;
}




int main()
{
    FileManager fm;
    Display d;
    PlayerManager pm;
    Caro cr;

    for(int i = 0; i<N; i++)
        for(int j = 0; j<N;j++)
            mask[i][j] = 0;
    vector<Cell> lastReplay; //= {Cell(2,3), Cell(1,2), Cell(5,6), Cell(7,8)};
    Cell c;
    int opt;

    vector<Player> players;/* = {Player("Tran Van Hanh", 5, 2, 1),Player("Nguyen Thanh Cong", 2, 5, 1),Player("Tran Van Hanh", 2, 2, 5),
                              Player("Tran Van Hao", 2, 3, 1),Player("Tran Huu Hanh", 2, 4, 2),Player("Vuong Dinh An", 2, 2, 10),
                              Player("Tran Huu Hung", 4, 2, 1),Player("Le Van Hanh", 2, 2, 3), Player("Nguyen Thi Kieu", 3, 2, 5)};
    cout<<endl;*/



    try{
        players = fm.loadPlayersInfo("players.txt");
    } catch(const FileHandlingException& ex){
        std::cerr<<ex.what()<<std::endl;
    }
    catch(const exception& ex){
        std::cerr<<ex.what()<<std::endl;
    }



    do{
        system("clear");
        //std::cout<< u8"\033[2J\033[1;1H";
        d.displayMenu();
        cout<<"\nNhập lựa chọn: ";
        opt = validOpt(opt,1,6);


        //cout<<opt;
        if(opt == 6) break;

        if(opt == 1){ // Vào luồng 2 player chơi với nhau

                continuePlayPreviousMatch(fm,d,cr);

                Player *player1, *player2;
                int player1_idx = -1, player2_idx = -1;
                std::cout<< u8"\033[2J\033[1;1H";
                std::cout<<"\nPlayer 1:";
                cout<<"\nPress number to choice";
                std::cout<<"\n1. Create a new player ";
                std::cout<<"\n2. Choose a old player ";
                std::cout<<endl;
                int newOrOldPlayer;
                //cin>>newOrOldPlayer;

                newOrOldPlayer = validOpt(newOrOldPlayer, 1,2);
                //cout<<newOrOldPlayer;

                if(newOrOldPlayer == 1){ // create new player: 1. Input 2. Add to array 3. Save to file


                    player1  = new Player();
                    player1->inputNewPlayer();

                    players.push_back(*player1);
                    delete player1;
                    player1 = &players[players.size()-1];

                    thread t(&FileManager::savePlayersInfoToFile, &fm, "players.txt", std::ref(players)); // Lỗi truyền vào pointer
                    t.detach();

                    player1_idx = players.size()-1;
                    //savePlayersInfoToFile("players.txt",players);
                } else{   // Load old players
                    cout<<"Nhập tên player muốn tìm: ";
                    string name;
                    cin.clear();
                    cin.ignore(std::numeric_limits<streamsize>::max(), '\n');
                    getline(cin, name);


                    vector<int> index = pm.searchPlayerIndex(name, players);
                    cout<<"Choose one of old players (0,1,2,...): ";
                    int oldOpt = validOpt(oldOpt,0,index.size()-1);
                    player1 = &players[index[oldOpt]];
                    player1_idx = index[oldOpt];
                    // cout<<" "<<oldOpt;
                    // cout<<" "<<player1_idx;
                    // cin>>player1_idx;
                }

                std::cout<< u8"\033[2J\033[1;1H";
                std::cout<<"\nPlayer 2:";
                cout<<"\nPress number to choice:";
                std::cout<<"\n1. Create a new player ";
                std::cout<<"\n2. Choose a old player\n";

                newOrOldPlayer = validOpt(newOrOldPlayer, 1,2);
                //cout<<newOrOldPlayer;

                if(newOrOldPlayer == 1){ // create new player
                    // default copy constructor
                    player2 = new Player();
                    player2->inputNewPlayer();
                    players.push_back(*player2);// copy
                    delete player2;
                    player2 = &players[players.size()-1];
                    thread t(&FileManager::savePlayersInfoToFile, &fm, "players.txt", std::ref(players)); // Chú ý: (1)Truyền địa chỉ đối tượng + địa chỉ thành viên hàm. (2) Lỗi truyền vào pointer
                    t.detach();
                    player2_idx = players.size()-1;
                    //savePlayersInfoToFile("players.txt",players);
                } else{   // Load old players
                    cout<<"Nhập tên player muốn tìm: ";
                    string name;
                    cin.clear();
                    cin.ignore(std::numeric_limits<streamsize>::max(), '\n');
                    getline(cin, name);
                    vector<int> index = pm.searchPlayerIndex(name, players);
                    cout<<"Choose one of old players (0,1,2,...): ";
                    int oldOpt = validOpt(oldOpt,0,index.size()-1);
                    player2 = &players[index[oldOpt]];
                    player2_idx = index[oldOpt];
                    // cout<<" "<<oldOpt;
                    // cout<<" "<<player2_idx;
                    // player2->displayPlayerInfo();
                    // cin>>player2_idx;
                }




                //std::cout<< u8"\033[2J\033[1;1H";
                //cout<<"\nCreating a match";
                Match m;
                m.newMatch(player1,player2);

                for(int i = 0; i<2*N + 1; i++)
                    for(int j = 0; j<4*N + 1; j++)
                         display[i][j] = 0;
                d.displayCaroTableWithMask(display);

                // Test expand--> Đoạn code lặp lại thì cho vào 1 hàm
                int turn = 1;
                do{
                    cout<<"\nPlayer "<<turn<<" move: ";
                    cin>>c.x>>c.y;
                    while(mask[c.x][c.y]!=0||c.x>=N||c.y>=N||c.x<=-1||c.y<=-1){
                        cout<<"Ô này không đánh được.Yêu cầu nhập lại: ";
                        cin>>c.x>>c.y;
                    }

                    //Cập nhật 4 cấu trúc dữ liệu
                    display[2*c.x + 1 ][4*c.y+2] = turn; // display là để hiển thị trạng thái
                    mask[c.x][c.y] = turn;  //trạng thái đánh hiện tại
                    lastReplay.push_back(c); // thứ tự đánh (0,1) -> (2,1) -> (3,2)
                    m.getReplay().push_back(c);

                    //std::cout<< u8"\033[2J\033[1;1H";
                    // Hiển thị sau khi đánh
                    system("clear");
                    d.displayCaroTableWithMask(display);

                    m.save("match.txt");

                    if(cr.winCheck(mask)!=0){
                        int temp = cr.winCheck(mask);
                        // Cập nhật list, match, playerinfo-> Lưu vào file
                        if(temp == 1){ // người chơi 1 thắng
                            int win = players[player1_idx].getNumberOfWins();
                            players[player1_idx].setNumberOfWins(win + 1);
                            int loose = players[player2_idx].getNumberOfLooses();
                            players[player2_idx].setNumberOfLooses(loose+1);
                            m.setState(1);
                        }else{
                            int win = players[player2_idx].getNumberOfWins();
                            players[player2_idx].setNumberOfWins(win + 1);
                            int loose = players[player1_idx].getNumberOfLooses();
                            players[player1_idx].setNumberOfLooses(loose+1);
                            m.setState(2);
                           }
                      m.save("match.txt"); // lỗi ở việc chỉ số thắng thua
                        // report result

                      thread t2(&FileManager::savePlayersInfoToFile, &fm, "players.txt", std::ref(players)); // Chú Lỗi truyền vào function calling thay vì pointer
                        t2.detach();
                        break;

                    }
                    turn = 3 - turn;
                    if(lastReplay.size() == N*N) { // can optimize
                        m.setState(0);
                        cout<<"two player draw";

                        // Số trận hòa của 2 người chơi tăng
                        int draw = players[player1_idx].getNumberOfDraws();
                        players[player1_idx].setNumberOfDraws(draw + 1);
                        draw = players[player2_idx].getNumberOfDraws();
                        players[player2_idx].setNumberOfDraws(draw+1);

                        m.save("match.txt");

                        thread t3(&FileManager::savePlayersInfoToFile, &fm,"players.txt", std::ref(players)); // Chú Lỗi truyền vào function calling thay vì pointer
                        t3.detach();

                        break;
                    }
                }while(1);
            }
        else if (opt==2){
                // bot -> Lưu và play
                // ko cần cập nhật thông tin player về các bot đâu
                lastReplay.clear();
                lastReplay.shrink_to_fit();
                std::cout<< u8"\033[2J\033[1;1H";
                d.displayBotOption();
                cout<<endl;
                while( !(std::cin>>opt) || (opt<=0||opt>4)){
                    std::cout<<"\nOption không hợp lệ. Yêu cầu nhập lại: ";
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');;
                }

                Bot b;
                if (opt == 1)
                         b.setLevel("easy");
                else if(opt == 2){
                         b.setLevel("normal");
                }else if (opt == 3){
                         b.setLevel("hard");
                }

                for(int i = 0; i<2*N + 1; i++)
                    for(int j = 0; j<4*N + 1; j++)
                        display[i][j] = 0;
                std::cout<< u8"\033[2J\033[1;1H";
                system("clear");
                d.displayCaroTableWithMask(display);


                int turn = 1;
                do{
                    cout<<"\nPlayer "<<turn<<" move: \n";
                    if (turn == 1) cin>>c.x>>c.y;
                    else
                        c = b.readGame(lastReplay);
                    while(mask[c.x][c.y]!=0||c.x>=N||c.y>=N||c.x<=-1||c.y<=-1){
                        cout<<"Ô này không đánh được.Yêu cầu nhập lại: ";
                        cin>>c.x;
                        cin>>c.y;
                    }
                    if(c.x == -1){
                        cout<<"bot can not find the way. ";
                        break;
                    }

                    display[2*c.x + 1 ][4*c.y+2] = turn;
                    mask[c.x][c.y] = turn;
                    lastReplay.push_back(c);
                    std::cout<< u8"\033[2J\033[1;1H";

                    d.displayCaroTableWithMask(display);


                    if(cr.winCheck(mask)!=0){
                        break;
                    }

                    turn = 3 - turn;
                    if(lastReplay.size() == N*N) { // can optimize
                        cout<<"Player 1 draw with bot";
                        break;
                    }
                }while(1);

                if(opt == 4) continue;


            }
        else if(opt == 3)
            {
                // Show thông tin last match: player 1 và player 2, kết quả,...
                // last Replay có 2 th: ở trên RAM (player vs bot) + ở trên disk (player vs player)
                cout<<"\n1. Press random number and enter to replay: \n";
                if(lastReplay.size() != 0)
                    cr.replay(lastReplay);
                else{
                    Match m = fm.loadMatch("match.txt");
                    cr.replay(m.getReplay());
                    m.showWinner();
                }
            }
        else if(opt == 4){ //player's info
                std::cout<< u8"\033[2J\033[1;1H";
                d.displayPlayerInfoOption();
                cout<<endl;
                int infoOpt = validOpt(infoOpt,1,4);


                if(infoOpt == 1) //display play name
                    for(int i = 0; i<players.size(); i++){
                        players[i].displayPlayerInfoWithRanks();
                    }
                else if (infoOpt == 3) //find player
                {
                    cout<<"Nhập tên player muốn tìm: ";
                    string name;
                    cin.clear();
                    cin.ignore(std::numeric_limits<streamsize>::max(), '\n');
                    getline(cin, name);
                    vector<Player> foundPlayers = pm.searchPlayer(name, players);

                    cout<<"Hiện thị các player cùng rank với player ở trên:\n";

                    for(auto foundPlayer:foundPlayers){
                        pm.findEquivalentPlayers(foundPlayer,players);
                    }


                }
                else if( infoOpt == 2) // thêm player
                {
                    // default copy constructor
                    Player* p  = new Player();
                    p->inputNewPlayer();
                    players.push_back(*p);
                    delete p;
                    p = &players[players.size()-1];

                    thread t(&FileManager::savePlayersInfoToFile, &fm,"players.txt", std::ref(players)); // Lỗi truyền vào pointer
                    t.detach();

                }
                else if (infoOpt == 4) // same rank
                {
                    std::cout<< u8"\033[2J\033[1;1H";
                    cout<<"Nhập rank: ";
                    int rank; cin>>rank;

                    for(auto player: players)
                        if(player.getRank() == rank) player.displayPlayerInfoWithRanks();
                }

            }
        else if(opt == 5){ // guild
                std::cout<< u8"\033[2J\033[1;1H";
                try{
                    fm.readGuild("guild.txt");
                } catch(const FileHandlingException& ex){
                    std::cerr<<ex.what()<<std::endl;
                }
                catch(const exception& ex){
                    std::cerr<<ex.what()<<std::endl;
                }
            }
        char gOpt;
        cout<<"\nBack to menu (choose any character with enter): ";
        cin>>gOpt;
    }while(1);






    return 0;
}





























///------------------------------------- Code nháp

// Match loadMatch(string address){
//     ifstream file(address);

//     if(!file){
//         throw FileHandlingException("Can not open file to read");
//     }

//     std::string line;
//     std::getline(file, line);
//     std::getline(file, line);
//     std::getline(file, line);


//     Match m;
//     std::vector<Cell> replay;
//     // This code Using code from ChatGPT
//     while (std::getline(file, line)) {
//         size_t pos = 0;
//         while (pos < line.size()) {
//             if (line[pos] == '(') {
//                 size_t comma = line.find(',', pos);
//                 size_t end = line.find(')', pos);
//                 if (comma != std::string::npos && end != std::string::npos) {
//                     int x = std::stoi(line.substr(pos + 1, comma - pos - 1));
//                     int y = std::stoi(line.substr(comma + 1, end - comma - 1));
//                     replay.push_back({x, y});
//                     pos = end + 1;
//                 } else {
//                     break; // Error in format
//                 }
//             } else {
//                 ++pos;
//             }
//         }
//     }
//     m.getReplay() = replay;
//     return m;

// }

/*
2 p/a:
       p/a 1: Directly parsing by file
       p/a 2: isstream
*/


//#define LOAD_FILE_OPT1
#define LOAD_FILE_OPT2

#ifdef  LOAD_FILE_OPT1
vector<Player>  loadPlayersInfo(string address){

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
#endif

#ifdef LOAD_FILE_OPT2
// using ssstream
#endif

// void savePlayersInfoToFile(string address, vector<Player>& players){

//     ofstream file(address);

//     if (!file){
//         throw::FileHandlingException("Can not open file");
//        // cerr<<"Can not open file"<<endl;
//     }

//     // đẩy data vào file
//     for(auto &player: players){
//         file<<player.getName()<<", "<<player.getNumberOfWins()<<", "<<player.getNumberOfLooses()<<", "<<player.getNumberOfDraws()<<"\n";
//         file.flush(); // xả trực tiếp dữ liệu vào file từ buffer associated với file object, không đợi đến khi file.close() mới xả
//     }

//     file.close();
//     cout<<"successfully save to file";
// }



// // 2 P/a: 4*N + 1 có cần thiết không?--> Làm logic bên dưới p xử lý phưc tạp hơn
// // Chọn P/a đơn giản, rồi adapting input với nhau
// int winCheck(int mask[][N]){

//     // Check hàng: Kiểm tra xem có n số liên tiếp = x;
//     for(int i = 0; i<N; i++ ){
//         for(int j = 0; j<N-WIN_LENGTH; j++){
//             int check = 0;
//             if(mask[i][j]!= 0)
//                 for(int k = 1; k<=WIN_LENGTH; k++ ){
//                     if  (mask[i][j] != mask[i][j+k]) break; else check++;
//                 }

//             if (check == 3) {
//                 cout<<"first element in win row: " <<"("<<i<<","<<j<<")"<<mask[i][j]<<endl;
//                 if(mask[i][j] == 1) cout<<"Player 1 win";
//                 if(mask[i][j] == 2) cout<<"Player 2 win";
//                return mask[i][j];
//             }


//         }
//     }

//     // Check Theo cột
//     for(int j = 0; j<N; j++ ){
//         for(int i = 0; i<N-WIN_LENGTH; i++){

//             int check = 0;
//             if(mask[i][j]!=0)
//                 for(int k = 1; k<WIN_LENGTH; k++ ){
//                     if( mask[i][j] != mask[i+k][j]) break;
//                     else check++;
//             }
//             if (check == WIN_LENGTH-1) {
//                 cout<<"first element in win column " <<i<<j<<mask[i][j]<<endl;
//                 if(mask[i][j] == 1) cout<<"Player 1 win";
//                 if(mask[i][j] == 2) cout<<"Player 2 win";
//                 return mask[i][j];
//             }
//         }
//     }

//     // Check Theo đường chéo 1
//     for(int j = 0; j<N-WIN_LENGTH; j++ ){
//         for(int i = 0; i<N-WIN_LENGTH; i++){
//             int check = 0;
//             if(mask[i][j]!=0)
//                 for(int k = 1; k<WIN_LENGTH; k++ ){
//                     if( mask[i][j] != mask[i+k][j+k]) break;
//                     else check++;
//                 }
//             if (check == WIN_LENGTH-1) {
//                 cout<<"first element in win diagonal " <<i<<j<<mask[i][j]<<endl;
//                 if(mask[i][j] == 1)cout<<"Player 1 win";
//                 if(mask[i][j] == 2) cout<<"Player 2 win";
//                 return mask[i][j];
//                 }
//             }
//         }


//     // lỗi
//     // Theo đường chéo 2 ~ O(n^2)
//     for(int i = 0; i<N-WIN_LENGTH; i++ ){
//             for(int j = N-1; j>=WIN_LENGTH; j--){
//                 int check = 0;
//                 if(mask[i][j]!=0)
//                     for(int k = 1; k<WIN_LENGTH; k++ ){
//                         if( mask[i][j] != mask[i+k][j-k]) break;
//                         else check++;
//                     }
//                 if (check == WIN_LENGTH-1) {
//                     cout<<"first element in win diagonal " <<i<<j<<mask[i][j]<<endl;
//                     if(mask[i][j] == 1)cout<<"Player 1 win";
//                     if(mask[i][j] == 2) cout<<"Player 2 win";
//                     return mask[i][j];
//                 }
//             }
//         }

//     return 0;
// }


// // Two option: Chiều ngược và chiều xuôi
// void replay(vector<Cell>& replay){
//     int display[2*N+1][4*N+1];

//     // cập nhật cấu trúc display
//     for(int i = 0; i<2*N + 1; i++)
//         for(int j = 0; j<4*N + 1; j++)
//             display[i][j] = 0;

//     // cập nhật cấu trúc mask
//     for(int i = 0; i<replay.size(); i++){
//         if(i%2)
//             mask[ replay[i].x ][ replay[i].y ] =1;
//         else
//               mask[replay[i].x][replay[i].y] =2;
//     }

//     Display d;
//     for(int i = 0; i<replay.size(); i++){
//         if(i%2) display[2*replay[i].x + 1][4*replay[i].y + 2] = 1;
//         else display[2*replay[i].x + 1][4*replay[i].y + 2] = 2;
//         d.displayCaroTableWithMask(display);
//         cout<<"Player "<<i%2<<" move:"<<replay[i].x<<","<<replay[i].y<<endl;
//         std::this_thread::sleep_for(chrono::seconds(2)); // thời gian luồng hiện tại chuyển sang chế độ ngủ

//         //std::cout<< u8"\033[2J\033[1;1H";
//     }
//     cout<<"\n Nhập kí tự bất kì và nhấn enter để kết thúc: "<<endl;
//     int delay;
//     cin>>delay;

// }


/*
Requirement:
1 ngày/ 1 requirement
Có được dùng và sử dụng code từ ChatGPT ko?
    --> 1. P/án 1: tái sủ dụng
    --> 2. P/án 2:
                1. Tự giải
                1. Xem ý tưởng code từ ChatGPT và tự code lại
    --> 3. P/án 3:
    --> 4. Những luồng phụ:
                Đừng bị cuốn theo --> Giải quyết sau

R1:
1. Tự xác định và viết requirement
    Chia nho va xac dinh cac task
2. Tự thiết kế tổng quan: Vẽ biểu đồ UML
    Consult with ChatGPT
3. Thiết kế chi tiết
4. Implementation

Task 1: Hien Console game:
    1.1 Boi do vai chu
Task 2: Hiện thị bảng caro:
    1.2 Pan 1: Print("---") và Print("|") và print nhiều lần
            1.2 Quay con trỏ về chỗ nào đó
    1.2 P/an 2: Vòng for: Trong 1 lần có 2 bước: Print(|) print(---) và Print(  )
    1.2 P/an 3: Theo chỉ số (i,j)
            (i,0) = |, (even,j) = |---|---|...., (old,j) = |   |   |....,
            (0,j) = {|}
Task 3: Hiển thị bảng caro với chữ x và chữ o:
    1.3 P/an 1: Dùng 1 bảng mask để đánh dấu true false!!. Và cập nhật bảng này

Task 4: Enter move:
    1. Cập nhật bảng true false
    2--> Checking winning status: Logic nào đó với Vòng lặp o(n^3)
            --> Làm sao check được với o(n^4)

                        1.Backtracking -> check(i,j+1), check(j+1,i), check(j+1,j+1), check(j-1,j-1)
                                    ==> 1. Tìm đường đi rồi--> cần điều chỉnh ở đoạn sauko ổn
                        2. Check 3 chiều: Tìm 2 đầu hàng xóm xa nhất của mỗi đầu
                                 Tính khoảng cách 2 đầu đó --> =4 --> ok
                          2.-> Đánh dấu những điểm check rồi để ko quay lại
                            ==> ChatGPT tối ưu hơn
                        3. Base case: i,j thuộc {0,9} hoặc đi được 4 bước

---------------------------------------------------------------------------------
R2:
    3.--> Tạo bot:
        Easy: P/an 1: Tự làm-Random
        Medium, hard:
            P/an 1: Tái sử dụng thuật toán Minimax:
                1. Đọc lý thuyết và tự implement
                2. Đọc article và tictactoe và tự implement lại
                3. Đọc code chatGPT và tự implement lại
            P/an 2: Sử dụng AI để dự đoán
        Option: Undo và Redo từng bước


---------------------------------------------------------------------------------

R3:
    1. Redo với undo:
            Phương án: Lưu các nước vào trong 1 mảng rồi tạo vòng for display
            Lưu trữ move:
                    bảng 1 chiều:[k] = (i,j): Play 1 (index 0 --> x), Play 2(index lẻ --> o)
            Watch replay:
                1. Đi ngược lại từ bước cuối --> đầu
                2. Từ bước đầu --> cuối
                3. delay
                4. Lưu lại ván cuối sau khi đánh
R4:
    1. File txt để quản lý thông tin player
            P/an: OOP+ Save file
    2. ShowInfo của player, và các player cùng level
            1. Quét xem player có điểm số sát với player hiện tại thì in ra
            2. Show bảng xếp hạng --> Đánh điểm số
            3. Tìm các players cùng level:
                    Thêm trường level:
                        Level 1: 0 -> 5
                        Level 2: 5 -> 9
                        Level 3: 9 -> 12
                        Level 4: 10 -> 11
                        Level 5: > 11
            4. Định nghĩa level (how):
                    1. Định nghĩa theo số trận thắng và số trận thua
                    2. Định nghĩa theo tỉ số đối đầu giữa 2 player
    3. Lưu info của trận đấu:
            1.Player
            2. Tỉ số
            3. Replay của Trận đấu

    4. Bảng xếp hạng

    5. Option:
            1. Lưu trận đánh đang giở
            2. Một nút thoát ra khi đang đánh
            3. Tái tạo trận đánh đó và đánh tiếp


Tổng kết: Còn phần loadMatch
*/



// pm.rankingPlayers(players);
// cout<<endl;


// for(int i = 0; i<players.size(); i++){
//     players[i].displayPlayerInfoWithRanks();
// }

// pm.findEquivalentPlayers(players[1],players);


//// Try catch 1:
// try{
//     loadPlayersInfo("players.txt");
// }catch (std::runtime_error& ex){
//     std::cerr<<ex.what()<<endl;
//     ofstream file("players.txt"); // create file
//     if(!file){
//         cout<<"Can not create file";
//         return 1;
//     }
//     cout<<"Successful creating file";
// }

// try {
//     auto p = readFile("players.txt");
// }
// catch(const FileHandlingException& ex){
//     std::cerr<<"can not read file"<<ex.what()<<std::endl;
// }
// catch (const exception& ex){
//     std::cerr<<ex.what()<<std::endl;
// }


// try{
//     savePlayersInfoToFile("players.txt", players);
// }catch(const FileHandlingException& ex){
//     std::cerr<<ex.what()<<std::endl;
// }
// catch(const exception& ex){
//     std::cerr<<ex.what()<<std::endl;
// }


// for(int i = 0; i<N; i++ )
//     for(int j = 0; j<N; j++) mask[i][j] = display[2*i+1][4*j+2];
// winCheck(mask);
// mask1[2][2] = 1;
// mask1[3][3] = 1;
// mask1[4][4] = 1;
// mask1[5][5] = 1;
// cout<<"check: "<< winCheck(mask)<<endl;

// for(int i = 0; i<N; i++ )
// {
//     for(int j = 0; j<N; j++) cout<<mask[i][j];
//     cout<<endl;
// }

/*
        Cần phải xử lý:
           1. Player 1: Add a new player or choose a old player
           2. Player 2:
                Th a new player: Nhập tên --> Lưu vào file
                Player cũ bỏ qua
           3."Are you ready to play?"

           4. Sau khi xong match
                   Cập nhật player1 Info + player2 Info
                   Lưu lastPlay và lastMatch?
                       lastReplay có thể exit và mở được lại --> trên ổ cứng
                       lastMatch có thể lưu các match cũ để show ra
                            TH: Lúc chọn option và sau khi exit()
            5. Match bị quit lúc giở trận
                    -> Lưu lại match --> Sau đó access lại match này
        */



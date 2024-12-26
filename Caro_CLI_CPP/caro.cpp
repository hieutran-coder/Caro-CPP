#include "caro.h"

Caro::Caro() {}




int Caro::winCheck(int mask[][10]){
    const int WIN_LENGTH = 4;
    const int N = 10;
    // Check hàng: Kiểm tra xem có n số liên tiếp = x;
    for(int i = 0; i<N; i++ ){
        for(int j = 0; j<N-WIN_LENGTH; j++){
            int check = 0;
            if(mask[i][j]!= 0)
                for(int k = 1; k<=WIN_LENGTH; k++ ){
                    if  (mask[i][j] != mask[i][j+k]) break; else check++;
                }

            if (check == 3) {
                cout<<"Player "<<mask[i][j]<<" win with first element in win row: " <<"("<<i<<","<<j<<") "<<endl;
                if(mask[i][j] == 1) cout<<"Player 1 win";
                if(mask[i][j] == 2) cout<<"Player 2 win";
                return mask[i][j];
            }


        }
    }

    // Check Theo cột
    for(int j = 0; j<N; j++ ){
        for(int i = 0; i<N-WIN_LENGTH; i++){

            int check = 0;
            if(mask[i][j]!=0)
                for(int k = 1; k<WIN_LENGTH; k++ ){
                    if( mask[i][j] != mask[i+k][j]) break;
                    else check++;
                }
            if (check == WIN_LENGTH-1) {
                cout<<"First element in win column " <<i<<j<<mask[i][j]<<endl;
                if(mask[i][j] == 1) cout<<"Player 1 win";
                if(mask[i][j] == 2) cout<<"Player 2 win";
                return mask[i][j];
            }
        }
    }

    // Check Theo đường chéo 1
    for(int j = 0; j<N-WIN_LENGTH; j++ ){
        for(int i = 0; i<N-WIN_LENGTH; i++){
            int check = 0;
            if(mask[i][j]!=0)
                for(int k = 1; k<WIN_LENGTH; k++ ){
                    if( mask[i][j] != mask[i+k][j+k]) break;
                    else check++;
                }
            if (check == WIN_LENGTH-1) {
                cout<<"First element in win diagonal " <<i<<j<<mask[i][j]<<endl;
                if(mask[i][j] == 1)cout<<"Player 1 win";
                if(mask[i][j] == 2) cout<<"Player 2 win";
                return mask[i][j];
            }
        }
    }



    // code fixed from chatGPT
    for (int i = 0; i <= N - WIN_LENGTH; ++i) {
        for (int j = WIN_LENGTH - 1; j < N; ++j) {
            int check = 0;
            if (mask[i][j] != 0) {
                for (int k = 1; k < WIN_LENGTH; ++k) {
                    if (mask[i][j] != mask[i + k][j - k]) break;
                    else check++;
                }
            }
            if (check == WIN_LENGTH - 1) {
                std::cout << "First element in win diagonal: (" << i << "," << j << ") " << mask[i][j] << std::endl;
                if (mask[i][j] == 1) std::cout << "Player 1 win";
                if (mask[i][j] == 2) std::cout << "Player 2 win";
                return mask[i][j];
            }
        }
    }


    return 0;
}



// Two option: Chiều ngược và chiều xuôi
void Caro::replay(vector<Cell>& replay){
    const int WIN_LENGTH = 4;
    const int N = 10;
    int display[2*N+1][4*N+1];

    // cập nhật cấu trúc display
    for(int i = 0; i<2*N + 1; i++)
        for(int j = 0; j<4*N + 1; j++)
            display[i][j] = 0;

    // // Replay ko cập nhật cấu trúc mask
    // for(int i = 0; i<replay.size(); i++){
    //     if(i%2)
    //         mask[ replay[i].x ][ replay[i].y ] =1;
    //     else
    //         mask[replay[i].x][replay[i].y] =2;
    // }

    Display d;
    for(int i = 0; i<replay.size(); i++){
        if(i%2) display[2*replay[i].x + 1][4*replay[i].y + 2] = 1;
        else display[2*replay[i].x + 1][4*replay[i].y + 2] = 2;
        d.displayCaroTableWithMask(display);
        cout<<"Player "<<i%2<<" move:"<<replay[i].x<<","<<replay[i].y<<endl;
        std::this_thread::sleep_for(chrono::seconds(2)); // thời gian luồng hiện tại chuyển sang chế độ ngủ

        //std::cout<< u8"\033[2J\033[1;1H";
    }
    cout<<"---Nhập kí tự bất kì và nhấn enter để kết thúc quá trình replay--- ";
    int delay;
    cin>>delay;

}


// // lỗi
// // Theo đường chéo 2 ~ O(n^2)
// for(int i = 0; i<N-WIN_LENGTH; i++ ){
//     for(int j = N-1; j>=WIN_LENGTH; j--){
//         int check = 0;
//         if(mask[i][j]!=0)
//             for(int k = 1; k<WIN_LENGTH; k++ ){
//                 if( mask[i][j] != mask[i+k][j-k]) break;
//                 else check++;
//             }
//         if (check == WIN_LENGTH-1) {
//             cout<<"first element in win diagonal " <<i<<j<<mask[i][j]<<endl;
//             if(mask[i][j] == 1)cout<<"Player 1 win";
//             if(mask[i][j] == 2) cout<<"Player 2 win";
//             return mask[i][j];
//         }
//     }
// }

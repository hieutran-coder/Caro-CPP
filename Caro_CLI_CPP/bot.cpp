#include "bot.h"

string Bot::getLevel() const
{
    return level;
}

void Bot::setLevel(const string &newLevel)
{
    level = newLevel;
}

Bot::Bot() {}


int getRandomNumber(int min, int max) {
    return min + rand() % (max - min + 1);
}



bool checkCell(int i, int j){

    if(i>9||j>9||i<0||j<0) return false;
    else return true;

}


// From ChatGPT
int evaluateLine(int countBot, int countPlayer) {
    if (countBot == 4) return -100;  // Bot wins
    if (countPlayer == 4) return 100;  // Player wins
    if (countBot == 3 && countPlayer == 0) return -10;  // Bot has three in a row
    if (countBot == 2 && countPlayer == 0) return -5;  // Bot has two in a row
    if (countPlayer == 3 && countBot == 0) return 10;  // Player has three in a row
    if (countPlayer == 2 && countBot == 0) return 5;  // Player has two in a row
    return 0;
}

// From ChatGPT
#define SOLUTION1
#ifdef SOLUTION1


// // ChatGPT
int evaluateBoard(int mask[10][10]) {
    int score = 0;

    // Evaluate rows: Caculate number of Bot and Player
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j <= 10 - 4; j++) {
            int countBot = 0;
            int countPlayer = 0;
            for (int k = 0; k < 4; k++) {
                if (mask[i][j + k] == 2) countBot++;
                if (mask[i][j + k] == 1) countPlayer++;
            }
            score += evaluateLine(countBot, countPlayer);
        }
    }

    // Evaluate columns
    for (int j = 0; j < 10; j++) {
        for (int i = 0; i <= 10 - 4; i++) {
            int countBot = 0;
            int countPlayer = 0;
            for (int k = 0; k < 4; k++) {
                if (mask[i + k][j] == 2) countBot++;
                if (mask[i + k][j] == 1) countPlayer++;
            }
            score += evaluateLine(countBot, countPlayer);
        }
    }

    // Evaluate diagonals (top-left to bottom-right)
    for (int i = 0; i <= 10 - 4; i++) {
        for (int j = 0; j <= 10 - 4; j++) {
            int countBot = 0;
            int countPlayer = 0;
            for (int k = 0; k < 4; k++) {
                if (mask[i + k][j + k] == 2) countBot++;
                if (mask[i + k][j + k] == 1) countPlayer++;
            }
            score += evaluateLine(countBot, countPlayer);
        }
    }

    // Evaluate diagonals (bottom-left to top-right)
    for (int i = 0; i <= 10 - 4; i++) {
        for (int j = 3; j < 10; j++) {
            int countBot = 0;
            int countPlayer = 0;
            for (int k = 0; k < 4; k++) {
                if (mask[i + k][j - k] == 2) countBot++;
                if (mask[i + k][j - k] == 1) countPlayer++;
            }
            score += evaluateLine(countBot, countPlayer);
        }
    }

    return score;
}
#endif


// From ChatGPT
//#define SOLUTION2
#ifdef SOLUTION2
int evaluateBoard(int mask[10][10]) {
    int score = 0;
    return score;
}
#endif

int minimax(int mask[10][10], int depth, bool isBot) {
    int score = evaluateBoard(mask);
    if (depth == 2) return score;
    if (score == 100) return score - depth;  // player wins
    if (score == -100) return score + depth;  // bot wins

    bool movesLeft = false;
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            if (mask[i][j] == 0) {
                movesLeft = true;
                break;
            }
        }
    }
    if (!movesLeft) return 0;  // draw

    if (isBot) {
        int best = std::numeric_limits<int>::max();  // Bot minimizes the player's score
        for (int i = 0; i < 10; i++) {
            for (int j = 0; j < 10; j++) {
                if (mask[i][j] == 0) {
                    mask[i][j] = 2;  // Bot's move
                    best = std::min(best, minimax(mask, depth + 1, !isBot));
                    mask[i][j] = 0;
                }
            }
        }
        return best;
    } else {
        int best = std::numeric_limits<int>::min();  // Player maximizes the bot's score
        for (int i = 0; i < 10; i++) {
            for (int j = 0; j < 10; j++) {
                if (mask[i][j] == 0) {
                    mask[i][j] = 1;  // Player's move
                    best = std::max(best, minimax(mask, depth + 1, !isBot));
                    mask[i][j] = 0;
                }
            }
        }
        return best;
    }
}
// From ChatGPT
Cell findBestMove(int mask[10][10]) {
    int bestVal = std::numeric_limits<int>::max();  // Bot minimizes the player's score
    Cell bestMove(-1, -1);

    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            if (mask[i][j] == 0) {
                mask[i][j] = 2;  // Bot's move
                int moveVal = minimax(mask, 0, false);
                mask[i][j] = 0;
                if (moveVal < bestVal) {  // Since the bot minimizes
                    bestMove = Cell(i, j);
                    bestVal = moveVal;
                }
            }
        }
    }


    return bestMove;
}



Cell Bot::readGame( vector<Cell> &replay)
{

    // Seed the random number generator with the current time
    srand(static_cast<unsigned int>(time(0)));


    int mask[10][10];

    for(int i = 0; i<10; i++)
        for(int j = 0; j<9; j++){ mask[i][j] = 0;}

    // cập nhật cấu trúc mask
    for(int i = 0; i<replay.size(); i++){
        if(i%2)
            mask[ replay[i].x ][ replay[i].y ] =1;
        else
            mask[replay[i].x][replay[i].y] =2;
    }


    if(level == "easy"){
        // P/an 1: Đánh random

        //P/an 2: Duyệt từ cuối đến đầu: Đánh xung quanh cái ô x
        for(int cellIndex = replay.size() -1; cellIndex>=0; cellIndex--){

                int i = 1, j=1; // ô hàng xóm


                if(checkCell(replay[cellIndex].x + i,replay[cellIndex].y + j)){
                     if(mask[replay[cellIndex].x +i][ replay[cellIndex].y  +j]==0){
                        return Cell(replay[cellIndex].x + i,replay[cellIndex].y + j);
                    }
                }

                i = -1, j= -1;
                if(checkCell(replay[cellIndex].x + i,replay[cellIndex].y + j)){
                    if(mask[replay[cellIndex].x+i ][ replay[cellIndex].y+j  ]==0){
                        return Cell(replay[cellIndex].x + i,replay[cellIndex].y + j);
                    }
                }


                i = -1, j= 1;
                if(checkCell(replay[cellIndex].x + i,replay[cellIndex].y + j)){
                    if(mask[replay[cellIndex].x+i ][ replay[cellIndex].y+j  ]==0){
                        return Cell(replay[cellIndex].x + i,replay[cellIndex].y + j);
                    }
                }

                i = 1, j= -1;
                if(checkCell(replay[cellIndex].x + i,replay[cellIndex].y + j)){
                    if(mask[replay[cellIndex].x+i ][ replay[cellIndex].y+j  ]==0){
                        return Cell(replay[cellIndex].x + i,replay[cellIndex].y + j);
                    }
                }
            }

        for(int i = 0; i<10; i++)
            for(int j = 0; j<10; j++)
                if( mask[i][j] == 0) return Cell(i,j); // chưa được đánh

        return Cell(-1,-1);

    }


    if(level == "normal"){
       // Reuse code Minimax from chatGPT
        return findBestMove(mask);
    }

    if(level == "hard"){

        return findBestMove(mask); //// From ChatGPT
    }

}





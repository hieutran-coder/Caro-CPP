#include "carocontroller.h"
#include<QDebug>
#include<QVariantList>
#include<QTimer>
#include<thread>
CaroController::CaroController(QObject *parent)
    : QObject{parent}
{}

QVector<QVector<int> > CaroController::getCaro() const
{
    return caro;
}

void CaroController::setCaro(const QVector<QVector<int> > &newCaro)
{
    if (caro == newCaro)
        return;
    caro = newCaro;
    emit caroChanged();
}


void CaroController::move(int index){
    if(numberOfO==numberOfX){
        numberOfX++;
        matrix[index] =1;
    }
    else{
        numberOfO++;
        matrix[index] =2;
    }
    replay.push_back(   Cell((index-index%10)/10,index%10)  );
    showWinScreen = checkWin();

    qDebug()<<"showWinScreen: "<<showWinScreen;
    emit matrixChanged();
    emit showWinScreenChanged();
}





void CaroController::playWithBot(int index){
    if(numberOfO==numberOfX){
        numberOfX++;
        matrix[index] =1;
        replay.push_back(   Cell((index-index%10)/10,index%10)  );
        showWinScreen = checkWin();
        emit matrixChanged();
        // Schedule bot move in the next event loop iteration (ChatGPT)
        QTimer::singleShot(0, this, [this]() {  // Thời gian, tên đối tượng
            makeBotMove();
        });

    }
    else{
        makeBotMove();
    }

    qDebug()<<"showWinScreen: "<<showWinScreen;
    emit showWinScreenChanged();
}


void CaroController::replayLastMatch(){
    for(int i = 0; i<matrix.size(); i++) matrix[i] = 0;
    emit matrixChanged();


    // Replay the moves with a delay
    replayIndex = 0; // To keep track of the current move
    QTimer::singleShot(0, this, &CaroController::replayNextMove);


}

// Code reuse from ChatGPT for avoid block UI.
void CaroController::replayNextMove() {
    if (replayIndex >= replay.size()) {
        return; // End of replay
    }

    // Update the matrix with the next move
    matrix[replay[replayIndex].x * 10 + replay[replayIndex].y] = (replayIndex % 2) + 1;
    emit matrixChanged();
    replayIndex++;

    // Schedule the next move
    QTimer::singleShot(1000, this, &CaroController::replayNextMove); // Delay of 1 second
}

void CaroController::makeBotMove() {
    numberOfO++;
    bot.setLevel("hard");

    Cell botMove = bot.readGame(replay);
    if( matrix[botMove.x * 10 + botMove.y] ==0)
        matrix[botMove.x * 10 + botMove.y] = 2;
    emit matrixChanged();
    replay.push_back(   Cell(botMove.x,botMove.y)  );
    showWinScreen = checkWin();
    emit showWinScreenChanged();
}



void CaroController::setDefaultCaro(){

    this->caro.resize(10);
    for(int i = 0; i<10; i++){
        this->caro[i].resize(10);
        }

    for(int i =0; i<10; i++)
        for(int j = 0; j<10; j++)
            caro[i][j] = 0;

    emit caroChanged();
}

QVector<int> CaroController::getMatrix() const
{
    return matrix;
}




void CaroController::setMatrix(const QVector<int> &newMatrix)
{
    if (matrix == newMatrix)
        return;
    matrix = newMatrix;
    emit matrixChanged();
}
void CaroController::setMatrix()
{
    this->matrix.resize(100);
    for(int i = 0; i<matrix.size(); i++) matrix[i] = 0;
    emit matrixChanged();
}


int CaroController::checkWin(){

    int mask[10][10];
    for(int i = 0; i<matrix.size(); i++)
    {
        int x = (i-i%10)/10;
        int y = i%10;
        if (matrix[i] == 1) mask[x][y] = 1;
        else if (matrix[i] == 2) mask[x][y] = 2;
        else if (matrix[i] == 0) mask[x][y] = 0;
    }


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
                qDebug()<<"Player "<<mask[i][j]<<" win with first element in win row: " <<"("<<i<<","<<j<<") ";
                if(mask[i][j] == 1) qDebug()<<"Player 1 win";
                if(mask[i][j] == 2) qDebug()<<"Player 2 win";
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
                qDebug()<<"First element in win column " <<i<<j<<mask[i][j];
                if(mask[i][j] == 1) qDebug()<<"Player 1 win";
                if(mask[i][j] == 2) qDebug()<<"Player 2 win";
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
                qDebug()<<"First element in win diagonal " <<i<<j<<mask[i][j];
                if(mask[i][j] == 1)qDebug()<<"Player 1 win";
                if(mask[i][j] == 2) qDebug()<<"Player 2 win";
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
                qDebug() << "First element in win diagonal: (" << i << "," << j << ") " << mask[i][j];
                if (mask[i][j] == 1) qDebug() << "Player 1 win";
                if (mask[i][j] == 2) qDebug() << "Player 2 win";
                return mask[i][j];
            }
        }
    }


    return 0;
}

int CaroController::getShowWinScreen() const
{
    return showWinScreen;
}

void CaroController::setShowWinScreen(int newShowWinScreen)
{
    if (showWinScreen == newShowWinScreen)
        return;
    showWinScreen = newShowWinScreen;
    emit showWinScreenChanged();
}



// QVariantList CaroController::matrix() const
// {
//     QVariantList list;
//     for (const QVector<int>& row : caro) {
//         QVariantList rowList;
//         for (int value : row) {
//             rowList.append(value);
//         }
//         list.append(rowList);
//     }
//     return list;
// }

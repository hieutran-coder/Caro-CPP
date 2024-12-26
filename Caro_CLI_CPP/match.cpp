#include "match.h"

void Match::setReplay(const vector<Cell> &newReplay)
{
    Replay = newReplay;
}

vector<Cell>& Match::getReplay()
{
    return Replay;
}

int Match::getState() const
{
    return state;
}

void Match::setState(int newState)
{
    state = newState;
}

void Match::showWinner()
{
    if(this->state == 0) cout<<"\nDraw";
    if(this->state == 1) cout<<"\nPlayer 1 win";
    if(this->state == 2) cout<<"\nPlayer 2 win";
    if(this->state == -1) cout<<"==> Vẫn Chưa xác định được người thắng ";
}

void Match::save(string address)
{
    ofstream file(address);

    if (!file){
        throw::FileHandlingException("Can not open file");
        // cerr<<"Can not open file"<<endl;
    }

    // đẩy data vào file
    file<< p1->getName()<<" "<<p1->getNumberOfWins()<<" "
         <<p1->getNumberOfLooses()<<" "<<p1->getNumberOfDraws()<<"\n";

    file<< p2->getName()<<" "<<p2->getNumberOfWins()<<" "
         <<p2->getNumberOfLooses()<<" "<<p2->getNumberOfDraws()<<"\n";

    file<<state<<"\n";
    for(auto point:Replay){
        file<<"("<<point.x <<","<< point.y<<")";
    }
    file.close();
    //cout<<"successfully save to file";
}




Match::Match() {}

void Match::newMatch( Player* p1,  Player* p2)
{
    this->p1 = p1;
    this->p2 = p2;
}

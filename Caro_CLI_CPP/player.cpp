#include "player.h"

std::string Player::getName() const
{
    return name;
}

int Player::getNumberOfWins() const
{
    return numberOfWins;
}

int Player::getNumberOfDraws() const
{
    return numberOfDraws;
}

int Player::getNumberOfLooses() const
{
    return numberOfLooses;
}

int Player::getTotalPoints()
{
    return this->getNumberOfWins()*3 + this->numberOfDraws;
}

void Player::setNumberOfWins(int newNumberOfWins)
{
    numberOfWins = newNumberOfWins;
}

void Player::setNumberOfDraws(int newNumberOfDraws)
{
    numberOfDraws = newNumberOfDraws;
}

void Player::setNumberOfLooses(int newNumberOfLooses)
{
    numberOfLooses = newNumberOfLooses;
}

void Player::setName(const std::string &newName)
{
    name = newName;
}

Player::Player(): name(" "), numberOfWins(0), numberOfLooses(0), numberOfDraws(0){}

Player::Player(string name, int win, int loose, int draw)
    :name(name), numberOfWins(win), numberOfDraws(draw), numberOfLooses(loose) { }



void Player::displayPlayerInfo()
{
     cout<<setw(20)<<this->name
         <<setw(10)<<this->numberOfWins
         <<setw(10)<<this->numberOfDraws
         <<setw(10)<<this->numberOfLooses;
     cout<<endl;

}

void Player::displayPlayerInfoWithPoints()
{
    //cout.setf(ios::left,ios::adjustfield);
    cout<<setw(20)<<this->name
         <<setw(10)<<this->numberOfWins
         <<setw(10)<<this->numberOfDraws
         <<setw(10)<<this->numberOfLooses
         <<setw(10)<<this->getTotalPoints();
    cout<<endl;

}



void Player::displayPlayerInfoWithRanks()
{
    cout<<setw(20)<<this->name
         <<setw(10)<<this->numberOfWins
         <<setw(10)<<this->numberOfDraws
         <<setw(10)<<this->numberOfLooses
         <<setw(10)<<this->getTotalPoints()
         <<setw(10)<<this->getRank();
    cout<<endl;

}

int Player::getRank()
{
    int p = this->getTotalPoints();
    if (p<5) return 1;
    else if(p<11) return 2;
    else if (p<17) return 3;
    else if (p<24) return 4;
    else return 5;
}


void Player::input()
{
    cout<<"Nhập tên: "; getline(cin, name);
    cout<<"Nhập số trận thắng: "; cin>>numberOfWins;
    cout<<"Nhập số trận hòa: "; cin>>numberOfDraws;
    cout<<"Nhập số trận thua: "; cin>>numberOfLooses;
}


void Player::inputNewPlayer()
{
    cin.clear();
    cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
    cout<<"Nhập tên: ";
    getline(cin, name);
    numberOfWins = 0;numberOfDraws = 0;numberOfLooses = 0;
}
void displayTitle(){

    cout<<setw(20)<<"Họ tên"
        <<setw(10)<<"Số trận thắng"
        <<setw(10)<<"Số trận hòa"
        <<setw(10)<<"Số trận thua";

}

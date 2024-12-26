#include "display.h"

Display::Display() {}




void Display::displayMenu(){
    cout<<"*-------MAIN MENU-------*";
    cout<<"\nPress number to choice:";
    cout<<"\n1.Play with other Player";
    cout<<"\n2.Play with BOT";
    cout<<"\n3.Replay";
    cout<<"\n4.Player's Information";
    cout<<"\n5.Guild";
    cout<<"\n6.Exit";
    cout<<endl;
}

void Display::displayBotOption(){
    cout<<"\n*-------Play with BOT-------";
    cout<<"\nPress number to choice:";
    cout<<"\n1. Easy Mode";
    cout<<"\n2. Normal";
    cout<<"\n3. Hard Mode";
    cout<<"\n4. Back to MAIN MENU";
}

void Display::displayPlayerInfoOption(){
    cout<<"\nPress number to choice:";
    cout<<"\n1. Show all players information";
    cout<<"\n2. Add a player";
    cout<<"\n3. Find players by name";
    cout<<"\n4. Show all players in same rank";
}





// problem fit giữa move(i,j) với display -> solve
void Display::displayCaroTableWithMask(int display[][4*M+1]){
    for(int j = 0; j<4*M+1; j++)
        if(j%4 ==3) cout<<(j/2 -1)/2;
        else cout<<" ";
    for(int i = 0; i<2*M+1; i++)
    {
        cout<<endl;
        for(int j = 0; j<4*M+1; j++){
            //if(j == 0) cout<<"|";

            // Ko phụ thuộc vào mask
            if(j==0){
                if(i%2 ==1){ cout<<(i+1)/2 -1;}
                else cout<<" ";
            }
            if(i%2 == 0){
                if(j%4 == 0) cout<<"|";
                else cout<<"-";
            }

            // phụ thuộc vào mask
            if (i%2 == 1){
                if(j%4 == 0) cout<<"|";
                else if(j%4 == 2&& display[i][j]==1) cout<<"x";
                else if(j%4 == 2&& display[i][j]==2) cout<<"o";
                else cout<<" ";
            }
        }
    }
    cout<<endl;
    //cout<<"-------";
}

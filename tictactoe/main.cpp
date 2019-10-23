#include <iostream>
#include "players.h"
#include <string>
#include <sstream>

using namespace std;

bool checkwin(player& p);

void movep(player& p, bool& gamebool){
    //move of a player
    //gamebool referenced to stop the game after winning
    cout<< p.name<< " please enter move:"<<endl;
    string input;
    string decomp;//temporary storage of input tokens
    getline(cin, input);
    vector<int> move(5);
    stringstream s(input);
    int i =0;

    //extract individual components from input vector
    while(getline(s, decomp, ' ')){
        move[i] = atoi(decomp.c_str());
        if(move[i]>2||move[i]<0){
            //filter out illegal indices
            cout<<"illegal input try again"<<endl;
            return movep(p, gamebool);
        }
        i++;
    }
    if(i!=5){
        //if the input is not correct format (too many elements)
        cout<<"illegal input try again"<<endl;
        return movep(p, gamebool);
    }
    if(board[move[0]][move[1]][move[2]][move[3]][move[4]]==0){
        //if empty space, then place move into that space
        board[move[0]][move[1]][move[2]][move[3]][move[4]] = p.number;
        p.played.push_back(move);

    }else{
        cout<<"played on already"<<endl;
        return movep(p, gamebool);
    }


    if(checkwin(p)){
        //checks to see if player p won the game
        printboard();
        cout<<p.name<<" wins the game!"<<endl;
        gamebool = false;

    }




}


bool checkwin(player& p){
    //checks for the winning condition
    vector<vector<vector<int> > > groupofmoves = combinations(p.played);
    int wins = 0;//keeps track of number of 3 in a rows made
    for(int i=0; i<groupofmoves.size(); i++){//checks each combination of three points
        vector<vector<int> > threepoints = groupofmoves[i];
        vector<int> point1 = threepoints[0];
        vector<int> point2 = threepoints[1];
        vector<int> point3 = threepoints[2];

        if(checkcollinear(point1, point2, point3)){
            wins++;
        }
    }

    if(wins>2){
        //if three or more lines are formed by the player
        return true;
    }else{
        return false;
    }
}

int main() {
    bool gamerun = true;
    player p1;
    p1.number = 1;
    player p2;
    p2.number = 2;
    cout<<"player 1 name:"<<endl;
    cin>>p1.name;
    cout<<"player 2 name:"<<endl;
    cin>>p2.name;
    cin.ignore();//must clear input buffer for getline() to work later

    while(gamerun) {
        printboard();
        movep(p1, gamerun);
        if(!gamerun){
            break;
        }
        printboard();
        movep(p2, gamerun);
    }
    return 0;
}
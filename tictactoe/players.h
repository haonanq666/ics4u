
#ifndef INC_5DTICTACTOE_PLAYERS_H
#define INC_5DTICTACTOE_PLAYERS_H

#include <iostream>
#include <vector>
#include "linearalgebra.h"


struct player{
    //the players in the game
    std::string name;
    int number;
    std::vector<std::vector<int> > played;


};

int board[3][3][3][3][3];
//board for keeping track of who played where

std::vector<std::vector<std::vector<int> > > combinations(std::vector<std::vector<int> >& group_of_moves){
    //algorithm for finding all combinations of three elements from a vector
    using namespace std;
    vector<vector<vector<int> > > combs;
    for(int i =0; i<group_of_moves.size(); i++){//first element
        for(int j= i+1; j<group_of_moves.size(); j++){//second element
            for(int k = j+1; k<group_of_moves.size(); k++){//third element
                vector<vector<int> > threemove(3);
                threemove[0] = (group_of_moves[i]);
                threemove[1] = (group_of_moves[j]);
                threemove[2] = (group_of_moves[k]);
                combs.push_back(threemove);
            }
        }
    }

    return combs;
}

void printboard(){
    //outputs current gameboard
    std::cout<<std::endl;
    std::cout<<"===0==="<<std::endl;
    std::cout<<std::endl;
    for ( int i = 0; i < 3; i++ ){
        for ( int j = 0; j < 3; j++ ){
            for ( int k = 0; k < 3; k++ ){
                for ( int l = 0; l < 3; l++ ){
                    for ( int m = 0; m < 3; m++ ) {
                        //add braces to the left for better visual organization
                        if(k==0&&l==0&&m==0){
                            std::cout<<"⌈ ";
                        }else if(k==2&&l==2&&m==0){
                            std::cout<<"⌊ ";
                        }else if(m==0){
                            std::cout<<"| ";
                        }
                        std::cout << board[l][m][k][j][i] << " ";
                    }std::cout<<std::endl;

                }if(k!=2){std::cout<<"|"<<std::endl;}else{std::cout<<std::endl;}

            }if(j!=2){std::cout<<std::endl;}

        }if(i!=2){std::cout<<"==="<<i+1<<"==="<<std::endl;}//label the 5th dimension
        std::cout<<std::endl;

    }std::cout<<std::endl;
}

bool checkcollinear(std::vector<int>& point1, std::vector<int>& point2, std::vector<int>& point3){
    //check three points for collinearity
    using namespace std;
    vector<int> p1p2, p2p3, p1p3;

    //the three sides of a triangle made by these three points
    p1p2 = subtract(point2, point1);
    p2p3 = subtract(point3, point2);
    p1p3 = subtract(point3, point1);

    double a, b, c, s;

    a = magnitude(p1p2);
    b = magnitude(p2p3);
    c = magnitude(p1p3);
    s = (a+b+c)/2;
    //using heron's formula
    double area;
    area = s*(s-a)*(s-b)*(s-c);

    return (area == 0);





}
#endif //INC_5DTICTACTOE_PLAYERS_H

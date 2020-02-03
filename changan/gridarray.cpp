#include "gridarray.h"
#include <QDebug>
#include <random>
#include <QDateTime>
#include <QVector>

//random algorithm
int getRand(int min, int max){
    unsigned int mt = static_cast<unsigned>(QDateTime::currentMSecsSinceEpoch());
    std::mt19937 gen(mt);
    std::uniform_int_distribution<> rd(min, max);
    return rd(gen);
}

int randint(){
    return getRand(0, 71);
}

/* the grid is a one dimensional character array that uses a specific character to
 * denote the condition that is happening in the grid. It will be spliced with algorithms
 * mimic a two dimensional playing area. This class used for majority of algorithmic manipulations
 * and works in conjunction with the maingamewindow to display the game to user. */

//begin, end iterators for ease of iteration through grid
char* GridArray::begin(){
    return gridarray;
}
char* GridArray::end(){
    return gridarray +72;
}

//print to console, debugging purposes.
void GridArray::printarray(){
    for(int i = 0; i<8; i++){
         //auto qout = qDebug();
         for(int k=0; k<9; k++) {
             //qout << *(gridarray+i*9+k);
             //qDebug() not needed for final product but left here for testing
          }
     }
}


void GridArray::changeelement(int location, char ch){
    *(gridarray+location) = ch;
}

//if pointer not in grid array, return 'o' to indicate out of bounds
char* GridArray::gettopneighbor(char* element){
    char* n = element - 9;
    if(n>=gridarray&&n<gridarray+9*8)return n;
    else return obchar;
}
char* GridArray::getbottomneighbor(char* element){
    char* n = element + 9;
    if(n>=gridarray&&n<gridarray+9*8)return n;
    else return obchar;
}
char* GridArray::getleftneighbor(char *element){
    char* n = element;
    if((n-gridarray)%9==0)return obchar;
    else if(n>=gridarray&&n<gridarray+9*8)return n-1;
    else return obchar;
}
char* GridArray::getrightneighbor(char* element){
    char* n = element +1;
    if((n-gridarray)%9==0)return obchar;
    else if(n>=gridarray&&n<gridarray+9*8)return n;
    else return obchar;
}

//check so that the three locations are distinct and are only on allowed locations
void GridArray::setinitpos(){
    int a , b , c;
    a = randint();
    while(*(gridarray+a)=='h'){
        a = randint();
    }
    b = randint();
    c = randint();
    while(b==a||*(gridarray+b)=='h'){
        b = randint();
    }
    while(c==b||c==a||*(gridarray+c)=='h'){
        c = randint();
    }


    changeelement(a, 'w');
    changeelement(b, 'w');
    changeelement(c, 'w');
}

//only allow w to move into k
bool checkvalidneighbor(char* dir){
    if(*dir == 'k') return true;
    else return false;

}

char* GridArray::getrandneighbor(char* element){
    int numofneighbors=-1;
    char* left;
    char* right;
    char* up;
    char* down;

    //find all available neighbors and put in vector
    QVector<char*> neighbors;

    left = getleftneighbor(element);
    if(checkvalidneighbor(left)){

        numofneighbors++;
        neighbors.push_back(left);
    }
    right = getrightneighbor(element);
    if(checkvalidneighbor(right)){

        numofneighbors++;
        neighbors.push_back(right);
    }
    up = gettopneighbor(element);
    if(checkvalidneighbor(up)){

        numofneighbors++;
        neighbors.push_back(up);
    }
    down = getbottomneighbor(element);
    if(checkvalidneighbor(down)){

        numofneighbors++;
        neighbors.push_back(down);
    }
    if(numofneighbors==-1){
        return element;//no valid neighbors
    }else{
        int rand = getRand(0, numofneighbors);
        char* neigh = neighbors[rand];
        return neigh;
    }

}
void GridArray::updatemsgbox(QString msg){
    window->updatemsg(msg);
}

void GridArray::checkdiscovered(char *element){
    char up = *gettopneighbor(element);
    char down = *getbottomneighbor(element);
    char left = *getleftneighbor(element);
    char right = *getrightneighbor(element);


    //do not use else if here so that all armies can give out the warning if w passes by multiple
    if(up == 'l'||down=='l'||left=='l'||right=='l'){
        updatemsgbox("龙武军：found 狼卫 trace");
    }
    if(up == 'y'||down=='y'||left=='y'||right=='y'){
        updatemsgbox("右骁卫：found 狼卫 trace");
    }
    if(up == 'b'||down=='b'||left=='b'||right=='b'){
        updatemsgbox("旅贲军：found 狼卫 trace");
    }
}

//replace w with original char after moving out
char GridArray::reputchar(char* element){
    int place = static_cast<int>(element-gridarray);
    if( place ==  3||
        place ==  4||
        place ==  5||
        place == 12||
        place == 13||
        place == 14||
        place == 21||
        place == 22||
        place == 23||
        place == 26||
        place == 50||
        place == 71){

        return 'h';
    }else{
        return 'k';
    }
}


void GridArray::updatearray(){
    moves++;
    bool caught = false;
    updatemsgbox("");
    updatemsgbox("turn "+QString::number(moves));
    for(char* iter = begin(); iter!=end(); iter++){
        if(*iter == 'l'|| *iter=='y'||*iter=='b'){
            *iter = reputchar(iter);
        }
    }
    if(lvbenpos!=-1){
        if(*(gridarray+lvbenpos) == 'w'){
            lwleft--;
            caught = true;
            updatemsgbox("in "+window->gridbuttons[lvbenpos]->text()+" caught 狼卫");
        }
        changeelement(lvbenpos, 'b');
    }
    if(youxiaopos!=-1){

        if(*(gridarray+youxiaopos) == 'w'){
            lwleft--;
            caught = true;

            updatemsgbox("in "+window->gridbuttons[youxiaopos]->text()+" caught 狼卫");
        }
        changeelement(youxiaopos, 'y');
    }
    if(longwupos!=-1){

        if(*(gridarray+longwupos) == 'w'){
            lwleft--;
            caught = true;

            updatemsgbox("in "+window->gridbuttons[longwupos]->text()+" caught 狼卫");
        }
        changeelement(longwupos, 'l');
    }
    if(caught){
        updatemsgbox("狼卫 left："+QString::number(lwleft));
    }
    if(lwleft==0){
        updatemsgbox("\nyou win");

        //prevent further modification by user after win
        window->setEnabled(false);

        timer = new QTimer;
        timer->setSingleShot(true);

        //open end screen after delay
        connect(timer, SIGNAL(timeout()), this, SLOT(outwin()));
        timer->start(4000);
    }

    for(char* iter = begin(); iter!=end(); iter++){
        if(*iter == 'w'){
            checkdiscovered(iter);
            char* neighbor=getrandneighbor(iter);
            *neighbor = 'q';
            if(neighbor!=iter) *iter = 'k'; //must check so that w that does not move doesn't delete itself

        }
    }
    //replace temp q with w
    for(char* iter2 = begin(); iter2 != end(); iter2++){
        if(*iter2 =='q'){
            *iter2 = 'w';
        }
    }

}

//quit condition activiated by -1 moves
void GridArray::quitpressed(){
    moves = -1;
    updatemsgbox("\nquitting game...");
    window->setEnabled(false);
    timer = new QTimer;
    timer->setSingleShot(true);
    connect(timer, SIGNAL(timeout()), this, SLOT(outwin()));
    timer->start(3000);
}


//calls win screen and gives the number of moves taken
void GridArray::outwin(){

    window->player->stop();
    window->setVisible(false);

    delete timer;
    emit win(moves);

}

//update position if moved
void GridArray::updatelvben(int num){
    lvbenpos= num;
}
void GridArray::updatelongwu(int num){
    longwupos = num;
}
void GridArray::updateyouxiao(int num){
    youxiaopos = num;
}


void GridArray::nextbuttonpressed(){
    //when next button is clicked
        updatearray();
        //printarray();
        //array print to console not needed for final product left for future maintenance.
        //qDebug()<<'\n';
        //qDebug() not needed (same as above)
}
void GridArray::gridbtnpressed(int num){
}


GridArray::GridArray(MainGameWindow* screen){
    // meaning of all char
    // k = 空，无士兵或狼卫，非保护 empty
    // l = 龙武军 army1
    // y = 右骁卫 army2
    // b = 旅贲军 army3
    // w = 狼卫 terrorist
    // h = 保护（靖安司、皇宫、营地）protected place
    // o = 出界，非长安以内所有指针都以此代表 out of bounds
    // q = 临时代指狼卫 temporary represent terrorist

    obchar = new char('o');
    for(char* i = begin(); i != end(); i++){
         *i = 'k';
    }
    connect(screen, SIGNAL(nextbutton()), this, SLOT(nextbuttonpressed()));
    connect(screen, SIGNAL(gridpressed(int)), this, SLOT(gridbtnpressed(int)));
    window = screen;
    window->disablebtns();

    connect(screen, SIGNAL(lvbenmoved(int)), this, SLOT(updatelvben(int)));
    connect(screen, SIGNAL(longwumoved(int)), this, SLOT(updatelongwu(int)));
    connect(screen, SIGNAL(youxiaomoved(int)), this, SLOT(updateyouxiao(int)));

    lvbenpos = -1;
    youxiaopos = -1;
    longwupos = -1;
    moves = 0;

    for(char* iter = begin(); iter!=end(); iter++){
        if( (iter-gridarray) ==  3||
            (iter-gridarray) ==  4||
            (iter-gridarray) ==  5||
            (iter-gridarray) == 12||
            (iter-gridarray) == 13||
            (iter-gridarray) == 14||
            (iter-gridarray) == 21||
            (iter-gridarray) == 22||
            (iter-gridarray) == 23||
            (iter-gridarray) == 26||
            (iter-gridarray) == 50||
            (iter-gridarray) == 71){
            //set char for protected areas
                *iter = 'h';

        }

    }
    setinitpos();
    lwleft = 3;
    updatemsgbox("turn "+QString::number(++moves));
    connect(window, SIGNAL(quit()), this, SLOT(quitpressed()));




}
GridArray::~GridArray(){
    delete [] gridarray;
    delete obchar;
    delete window;
}


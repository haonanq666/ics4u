#ifndef GRIDARRAY_H
#define GRIDARRAY_H
#include <QObject>
#include "maingamewindow.h"

class GridArray : public QObject
{
    Q_OBJECT
public:
    GridArray(MainGameWindow* screen);
    ~GridArray();
    char* begin();
    char* end();
    void printarray();
    void changeelement(int location, char ch);
    char* getelementptr(int i, int j);
    char* gettopneighbor(char* element);
    char* getbottomneighbor(char* element);
    char* getleftneighbor(char* element);
    char* getrightneighbor(char* element);
    char* obchar; //initialize this with new char('o') or undefined misbehavior occurs
    void setinitpos();
    char* getrandneighbor(char* element);
    void updatearray();
    void updatemsgbox(QString msg);
    MainGameWindow* window;
    void checkdiscovered(char* element);
    int lvbenpos;
    int longwupos;
    int youxiaopos;
    char reputchar(char* element);
    int lwleft;
    QTimer* timer;
    int moves;
signals:
    void win(int);


public slots:
    void nextbuttonpressed();
    void gridbtnpressed(int num);

    void updatelvben(int num);
    void updatelongwu(int num);
    void updateyouxiao(int num);
    void outwin();
    void quitpressed();


private:
    char* gridarray = new char[72];



};

#endif // GRIDARRAY_H

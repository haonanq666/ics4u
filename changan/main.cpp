#include "maingamewindow.h"

#include "startscreen.h"
#include "endwindow.h"
#include <QApplication>
#include "gridarray.h"

int main(int argc, char *argv[])
{
    int exitcode=1;

    while(exitcode!=0){
        //if exit code is 1, restart the game
        QApplication a(argc, argv);
        StartScreen* s = new StartScreen;
        s->show();

        MainGameWindow* w = new MainGameWindow(s);

        GridArray* grid = new GridArray(w);

        endwindow* e = new endwindow(grid);
        exitcode= a.exec();
        delete e;
        //delete final endscreen here to prevent memory leak if looping through app multiple times

    }
    return exitcode;

}

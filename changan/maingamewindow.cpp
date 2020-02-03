#include "maingamewindow.h"
#include "ui_maingamewindow.h"
#include "startscreen.h"
#include "addbuttons.cpp"
#include <QDebug>


MainGameWindow::MainGameWindow(StartScreen* st, QWidget *parent)
    : QMainWindow(parent)
    , uigame(new Ui::MainGameWindow){
    
    uigame->setupUi(this);
    this->setWindowFlags(Qt::Widget | Qt::FramelessWindowHint);
    //remove top taskbar for more screen estate

    this->setFixedSize(QSize(1366, 768));
    this->setStyleSheet("background-color: rgb(242,236,222)");
    this->setWindowTitle("长安十二时辰");
    addbuttons();

    start = st;
    connect(st, SIGNAL(start()), this, SLOT(showwindow()));
    for(auto p: gridbuttons){
        connect(p, SIGNAL(clicked()), this, SLOT(gridbuttonpressed()));
    }
    uigame->msgbox->setReadOnly(true);
    uigame->youxiaoqi->setStyleSheet("background-color: transparent");
    uigame->lvbenqi->setStyleSheet("background-color: transparent");
    uigame->longwuqi->setStyleSheet("background-color: transparent");
    uigame->henge->setStyleSheet("background-color: transparent");
    //prevents the background of image from obstructing elements behind it

    for(int i =0; i<72; i++){
        if( (i) ==  3||
            (i) ==  4||
            (i) ==  5||
            (i) == 12||
            (i) == 13||
            (i) == 14||
            (i) == 21||
            (i) == 22||
            (i) == 23||
            (i) == 26||
            (i) == 50||
            (i) == 71){
            //these are the protected places, show up red
                gridbuttons[i]->setStyleSheet("color: #C3272B");

    }else{
            gridbuttons[i]->setStyleSheet("color: #000000");
        }



}
    uigame->msgbox->setStyleSheet("background-color: #FFFBF0");
    music= new QMediaPlaylist();
    music->addMedia(QUrl( "qrc:/screens/gamebgm.mp3"));
    music->setPlaybackMode(QMediaPlaylist::Loop);

    player = new QMediaPlayer();
    player->setPlaylist(music);
}


MainGameWindow::~MainGameWindow()
{
   delete uigame;
   delete music;
   delete player;
}

void MainGameWindow::showwindow(){
    this->show();
    delete start;
    //clean up memory for startscreen

    player->play();
    //start music here

}
void MainGameWindow::updatemsg(QString msg){
    uigame->msgbox->append(msg);
}
void MainGameWindow::enablebtns(){
    //enable all buttons
    for(auto p : gridbuttons){
        p->setEnabled(true);
    }
}
void MainGameWindow::disablebtns(){
    for (auto p : gridbuttons){
        p->setEnabled(false);
    }
}

void MainGameWindow::enablenext(){
    uigame->bNext->setEnabled(true);
    delete timer;
}

void MainGameWindow::on_bNext_clicked()
{
    timer = new QTimer;
    timer->setSingleShot(true);

    //delay the next button so it cannot be pressed immediately after
    connect(timer, SIGNAL(timeout()), this, SLOT(enablenext()));
    uigame->bNext->setEnabled(false);
    uigame->bLongwujun->setChecked(false);
    uigame->bLvbenjun->setChecked(false);
    uigame->bYouxiaowei->setChecked(false);
    emit nextbutton();
    timer->start(2000); //timer to delay the button

}

//only allow one troop button to be checked at one time
void MainGameWindow::on_bLongwujun_toggled(bool checked)
{
    if(checked){
        enablebtns();
        uigame->bYouxiaowei->setCheckable(false);
        uigame->bLvbenjun->setCheckable(false);
    }
    else{
        disablebtns();
        uigame->bYouxiaowei->setCheckable(true);
        uigame->bLvbenjun->setCheckable(true);
    }
}


void MainGameWindow::on_bLvbenjun_toggled(bool checked)
{
    if(checked){
        enablebtns();
        uigame->bLongwujun->setCheckable(false);
        uigame->bYouxiaowei->setCheckable(false);
    }
    else{
        disablebtns();
        uigame->bLongwujun->setCheckable(true);
        uigame->bYouxiaowei->setCheckable(true);
    }
}

void MainGameWindow::on_bYouxiaowei_toggled(bool checked)
{
    if(checked){
        enablebtns();
        uigame->bLongwujun->setCheckable(false);
        uigame->bLvbenjun->setCheckable(false);
    }
    else{
        disablebtns();
        uigame->bLongwujun->setCheckable(true);
        uigame->bLvbenjun->setCheckable(true);
    }
}

void MainGameWindow::gridbuttonpressed(){
    QPushButton* button = static_cast<QPushButton*>(sender());
    int count = 0;

    //get which button was pressed
    while(button!=gridbuttons[count]){
        count++;
        if(count>71){
            //this should not happen (button not in array)
            return;
        }
    }
    emit gridpressed(count);

    //find the horizontal/vertical location of button
    int hor = count%9;
    int vert = (count-hor)/9;

    //create location on button to draw flag
    QPoint point;
    point.setX(hor*70+80);
    point.setY(vert*70+190);

    if(uigame->bYouxiaowei->isChecked()){
        uigame->youxiaoqi->move(point);
        uigame->bYouxiaowei->setChecked(false);
        emit youxiaomoved(count);

    }else if(uigame->bLvbenjun->isChecked()){
        uigame->lvbenqi->move(point);
        uigame->bLvbenjun->setChecked(false);
        emit lvbenmoved(count);

    }else if(uigame->bLongwujun->isChecked()){
        uigame->longwuqi->move(point);
        uigame->bLongwujun->setChecked(false);
        emit longwumoved(count);

    }

}

//return army to base, not on map. -1 used to denote this position.
void MainGameWindow::on_returny_clicked()
{

    QPoint ypoint(870, 240);
    if(uigame->bYouxiaowei->isChecked()){
        uigame->youxiaoqi->move(ypoint);
        emit youxiaomoved(-1);
        uigame->bYouxiaowei->setChecked(false);
    }
}

void MainGameWindow::on_returnb_clicked()
{
    QPoint bpoint(870, 330);

    if(uigame->bLvbenjun->isChecked()){
        uigame->lvbenqi->move(bpoint);
        emit lvbenmoved(-1);
        uigame->bLvbenjun->setChecked(false);
    }
}

void MainGameWindow::on_returnl_clicked()
{
    QPoint lpoint(870, 420);

    if(uigame->bLongwujun->isChecked()){
        uigame->longwuqi->move(lpoint);
        emit longwumoved(-1);
        uigame->bLongwujun->setChecked(false);
    }
}


void MainGameWindow::on_bQuit_clicked()
{
    emit quit();
}

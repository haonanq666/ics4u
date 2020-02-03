#include "startscreen.h"
#include "ui_startscreen.h"
#include <QDebug>

StartScreen::StartScreen(QWidget *parent) :QMainWindow(parent),uistart(new Ui::StartScreen){
    uistart->setupUi(this);
    this->setFixedSize(QSize(1366, 768));
    this->setStyleSheet("background-color: rgb(242,236,222)");
    this->setWindowTitle("长安十二时辰");

    //timer to update clock
    timer = new QTimer;
    connect(timer, SIGNAL(timeout()), this, SLOT(paint()));
    timer->start(1000);

    uistart->xian->addstartscreen(this);
    QFont f( "AR PL UKai TW MBE", 40, QFont::Bold);
    uistart->ke->setFont( f);
    uistart->shichen->setFont(f);
    uistart->yueri->setFont(f);

    //set color of certain elements
    QString color = "#5D513C";
    uistart->shichen->setStyleSheet("color: "+color);
    uistart->ke->setStyleSheet("color: "+color);
    uistart->yueri->setStyleSheet("color: "+color);
    h = new helpwindow;
    //only create one helpwindow to show/hide, delete when moving on
    connect(h, SIGNAL(okaypressed()), this, SLOT(closehelp()));


}

StartScreen::~StartScreen()
{
    delete timer;
    delete uistart;

}


void StartScreen::on_pushButton_clicked()
{
    h->hide();
    delete h;
    //delete the pointer to prevent memory leak
    this->hide();
    emit start();

}

void StartScreen::paint(){
    QTime time = QTime::currentTime();
    int h = time.hour();

    //the twelve 时辰 (two hours each, each 时辰 has two different modifiers)
    //子、丑、寅、卯、辰、巳、午、未、申、酉、戌、亥。
    if(h==0){
        uistart->shichen->setText("子正");

    } else if(h==1){
        uistart->shichen->setText("丑初");

    }else if(h==2){
        uistart->shichen->setText("丑正");

    }else if(h==3){
        uistart->shichen->setText("寅初");

    }else if(h==4){
        uistart->shichen->setText("寅正");

    }else if(h==5){
        uistart->shichen->setText("卯初");

    }else if(h==6){
        uistart->shichen->setText("卯正");

    }else if(h==7){
        uistart->shichen->setText("辰初");

    }else if(h==8){
        uistart->shichen->setText("辰正");

    }else if(h==9){
        uistart->shichen->setText("巳初");

    }else if(h==10){
        uistart->shichen->setText("巳正");

    }else if(h==11){
        uistart->shichen->setText("午初");

    }else if(h==12){
        uistart->shichen->setText("午正");

    }else if(h==13){
        uistart->shichen->setText("未初");

    }else if(h==14){
        uistart->shichen->setText("未正");

    }else if(h==15){
        uistart->shichen->setText("申初");

    }else if(h==16){
        uistart->shichen->setText("申正");

    }else if(h==17){
        uistart->shichen->setText("酉初");

    }else if(h==18){
        uistart->shichen->setText("酉正");

    }else if(h==19){
        uistart->shichen->setText("戌初");

    }else if(h==20){
        uistart->shichen->setText("戌正");

    }else if(h==21){
        uistart->shichen->setText("亥初");

    }else if(h==22){
        uistart->shichen->setText("亥正");

    }else if(h==23){
        uistart->shichen->setText("子初");

    }

    //get more precise time (1,2,3 quarters into the hour)
    int min = time.minute();
    if(min>45){
        uistart->ke->setText("三刻");
    }else if(min>30){
        uistart->ke->setText("二刻");

    }else if(min>15){
        uistart->ke->setText("一刻");
    }else{
        uistart->ke->setText("");

    }

    //render the date
    QDate date = QDate::currentDate();
    uistart->yueri->setText(QString::number(date.year())+"年"+QString::number(date.month())+"月"+QString::number(date.day())+"日");
    emit clock();

}

void StartScreen::printclock(){

}



void StartScreen::on_phelp_clicked()
{
    h->show();
}

void StartScreen::closehelp(){
    h->hide();
}

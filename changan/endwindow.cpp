#include "endwindow.h"
#include "ui_endwindow.h"

endwindow::endwindow(GridArray* w, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::endwindow)
{
    ui->setupUi(this);
    this->setVisible(false);
    //not have this showing from the beginning
    this->setFixedSize(QSize(1366, 768));
    this->setStyleSheet("background-color: rgb(242,236,222)");
    this->setWindowTitle("长安十二时辰");

    ui->jia->setStyleSheet("background-color: transparent");
    ui->jiazi->setStyleSheet("background-color: transparent");
    //transparent background to prevent blocking elements behind

    QFont f( "Arial", 40, QFont::Bold);
    ui->winlabel->setFont(f);
    ui->winlabel->setStyleSheet("color: #FF4C00");
    ui->hscorelabel->setStyleSheet("color: #FF4C00");

    connect(w, SIGNAL(win(int)), this, SLOT(show(int)));
    music = new QMediaPlaylist();
    music->addMedia(QUrl("qrc:/screens/duangexing.mp3"));
    music->setPlaybackMode(QMediaPlaylist::Loop);
    //add the music
    grid = w;
    player = new QMediaPlayer();
    player->setPlaylist(music);




}

int endwindow::getscore(){
    int hs;
    std::string highscore;
    std::ifstream savefile;
    savefile.open("../changan/savefile.txt");
    std::getline(savefile, highscore);
    if(highscore==""){
        //in case nothing is in file
        highscore = "0";
    }
    savefile.close();
    hs = std::stoi(highscore);
    return hs;
}

void endwindow::writescore(int score){
    std::ofstream savefile;
    savefile.open("../changan/savefile.txt", std::ofstream::out | std::ofstream::trunc);

    savefile<<score<<std::endl;
    savefile.close();

}

void endwindow::show(int cond){
    delete grid; //no accessing grid after this; slot is called immediately after outwin() signal
    this->setVisible(true);

    int scoreh = getscore();
    if((cond<scoreh && cond>0)||scoreh == 0){
        //in case the file is empty, the current score is set as highscore
        writescore(cond);
        scoreh = cond;
    }

    //score count starts at 1, therefore number of moves is actually one less.
    //The display is adjusted (but savefile.txt is still original score count)
    ui->hscorelabel->setText("Highscore: "+ QString::number(getscore()-1));
    if(cond==-1){
        ui->winlabel->setText("You quit the game");
    }else{
        ui->winlabel->setText("You took: "+QString::number(cond-1)+" moves");
    }
    player->play();
    //start music here


}

endwindow::~endwindow()
{
    delete ui;
    delete music;
    delete player;
}

void endwindow::on_bexit_clicked()
{
    QCoreApplication::exit(0);
}

void endwindow::on_brestart_clicked()
{
    QCoreApplication::exit(1);
}

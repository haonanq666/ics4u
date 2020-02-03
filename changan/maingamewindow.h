#ifndef MAINGAMEWINDOW_H
#define MAINGAMEWINDOW_H

#include <QMainWindow>
#include <QVector>
#include <QPushButton>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include "startscreen.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainGameWindow; }
QT_END_NAMESPACE

class MainGameWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainGameWindow(StartScreen* st, QWidget *parent = nullptr);
    ~MainGameWindow();
    void addbuttons();
    QVector<QPushButton*> gridbuttons;
    StartScreen* start;
    void updatemsg(QString msg);
    void enablebtns();
    void disablebtns();
    QTimer* timer;
    QMediaPlaylist* music;
    QMediaPlayer* player;

signals:
    void nextbutton();
    void youxiaochecked();
    void longwuchecked();
    void lvbenchecked();
    void gridpressed(int);
    void lvbenmoved(int);
    void youxiaomoved(int);
    void longwumoved(int);
    void win(int);
    void quit();


    
public slots:
    void showwindow();
    void enablenext();

private slots:
    void on_bNext_clicked();

    void on_bLongwujun_toggled(bool checked);

    void on_bLvbenjun_toggled(bool checked);

    void on_bYouxiaowei_toggled(bool checked);
    void gridbuttonpressed();

    void on_returny_clicked();

    void on_returnb_clicked();

    void on_returnl_clicked();

    void on_bQuit_clicked();

private:
    Ui::MainGameWindow *uigame;
    
};

#endif // MAINGAMEWINDOW_H

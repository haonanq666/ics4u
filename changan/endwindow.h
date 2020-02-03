#ifndef ENDWINDOW_H
#define ENDWINDOW_H

#include <QMainWindow>
#include <QFile>
#include <QTextStream>
#include <QMediaPlayer>
#include <fstream>
#include <QMediaPlaylist>
#include "gridarray.h"

namespace Ui {
class endwindow;
}

class endwindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit endwindow(GridArray* w, QWidget *parent = nullptr);
    ~endwindow();
    QMediaPlaylist* music;
    QMediaPlayer* player;
    GridArray* grid;
    int getscore();
    void writescore(int score);

public slots:
    void show(int);

private slots:
    void on_bexit_clicked();

    void on_brestart_clicked();

private:
    Ui::endwindow *ui;
};

#endif // ENDWINDOW_H

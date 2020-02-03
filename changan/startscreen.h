#ifndef STARTSCREEN_H
#define STARTSCREEN_H

#include <QMainWindow>
#include <QTime>
#include <QTimer>
#include <QPainter>
#include <QtGui>
#include "helpwindow.h"

namespace Ui {
class StartScreen;
}

class StartScreen : public QMainWindow
{
    Q_OBJECT

public:
    explicit StartScreen(QWidget *parent = nullptr);
    ~StartScreen();
    QTimer* timer;
    helpwindow* h;

signals:
    void start();
    void clock();
private slots:

    void on_pushButton_clicked();
    void paint();
    void closehelp();
    void printclock();

    void on_phelp_clicked();

private:
    Ui::StartScreen *uistart;
};

#endif // STARTSCREEN_H
